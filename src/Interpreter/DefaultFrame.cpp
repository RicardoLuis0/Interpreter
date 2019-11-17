#include "Interpreter/DefaultFrame.h"

#include <algorithm>

#include "Util/InterpreterUtilDefinesMisc.h"

#include "Parser/VariableDefinition.h"
#include "Parser/ExpressionTerm.h"
#include "Interpreter/IntVariable.h"
#include "Interpreter/FloatVariable.h"
#include "Interpreter/StringVariable.h"
#include "Lexer/IntegerToken.h"
#include "Lexer/FloatToken.h"
#include "Lexer/StringToken.h"
#include "Interpreter/UserFunction.h"
#include "deflib.h"
#include "Interpreter/PrimitiveType.h"
#include "Parser/BinaryOperation.h"
#include "Lexer/SymbolToken.h"
#include "Interpreter/VoidType.h"
#include "Interpreter/Expression.h"
#include "Interpreter/ArrayType.h"
#include "Interpreter/AnyType.h"
#include "MyExcept/MyExcept.h"

using namespace Interpreter;

DefaultFrame::DefaultFrame(std::vector<std::shared_ptr<Parser::Definition>> defs,std::vector<std::string> library_imports):DefaultFrame(nullptr){
    for(std::string library:library_imports){
        import(this,library);
    }
    for(std::shared_ptr<Parser::Definition> def:defs){
        add_definition(def,true);
    }
    for(auto fl:functions){
        for(auto fd:fl.second){
            if(auto uf=std::dynamic_pointer_cast<UserFunction>(fd.second)){
                uf->proccess_delayed();
            }
        }
    }
}

DefaultFrame::DefaultFrame(DefaultFrame * p,std::shared_ptr<Parser::VariableDefinition> def):DefaultFrame(p){
    add_definition(std::make_shared<Parser::Definition>(Parser::DEFINITION_VAR,def,def->line_start,def->line_end),true);
}

DefaultFrame::DefaultFrame(DefaultFrame * p,Function * f):DefaultFrame(p){
    if(auto uf=dynamic_cast<UserFunction*>(f)){
        if(uf->function->variadic){
            if(uf->function->variadic_type){
                uf->variadic_type=Type::from_vartype(this,uf->function->variadic_type);
            }else{
                uf->variadic_type=Type::any_type();
            }
            variable_types.insert({uf->function->variadic_ident,std::make_shared<ArrayType>(uf->variadic_type,-1)});//variadic arguments are sizeless arrays
        }
    }
    add_parameters(f->get_parameters());
    is_function=true;
	self_function=f;
}

DefaultFrame::DefaultFrame(DefaultFrame * p):parent(p),static_frame(p?std::make_shared<DefaultFrame>(p->parent?p->static_frame.get():nullptr):nullptr),static_exec_frame(nullptr){//if p is global, static frame's parent is p (allow global values access from static context)
	if(p&&!p->parent){
		static_frame->parent=p;
	}
}

std::shared_ptr<Type> DefaultFrame::get_variable_type(std::string name){
    MAP_GET(variable_types,name,parent?parent->get_variable_type(name):nullptr)
}

std::vector<std::vector<FunctionParameter>> DefaultFrame::get_function_variants(std::string name){
    auto iter=functions.find(name);
    if(iter!=functions.end()){
        std::vector<std::vector<FunctionParameter>> out;
        for(auto p:iter->second){
            out.push_back(p.first);
        }
        return out;
    }else{
        return parent?parent->get_function_variants(name):std::vector<std::vector<FunctionParameter>>();
    }
}

std::shared_ptr<Function> DefaultFrame::get_function_local(std::string name,std::vector<FunctionParameter> param_types){
    auto iter1=functions.find(name);
    if(iter1!=functions.end()){
        auto iter2=iter1->second.find(param_types);//strict search
        if(iter2!=iter1->second.end()){
            return iter2->second;
        }else{
            iter2=std::find_if(iter1->second.begin(),iter1->second.end(),[param_types](const std::pair<std::vector<FunctionParameter>,std::shared_ptr<Function>> &p)->bool{//loose search
                if(param_types.size()==p.first.size()||(p.second->is_variadic()&&param_types.size()>=p.first.size())){
                    for(size_t i=0;i<p.first.size();i++){
                        if(!param_types[i].type->allows_implicit_cast(param_types[i].type,p.first[i].type))return false;
                    }
                    if(p.second->is_variadic()){//do extra tests
                        for(size_t i=p.first.size();i<param_types.size();i++){
                            if(!param_types[i].type->allows_implicit_cast(param_types[i].type,p.second->get_variadic_type()))return false;
                        }
                    }
                    return true;
                }else{
                    return false;
                }
            });
            if(iter2!=iter1->second.end()){
                return iter2->second;
            }
        }
    }
    return nullptr;
}

std::shared_ptr<Function> DefaultFrame::get_function(std::string name,std::vector<FunctionParameter> param_types){
    std::shared_ptr<Function> func=get_function_local(name,param_types);
    return func?func:parent?parent->get_function(name,param_types):nullptr;
}

void DefaultFrame::add_parameters(std::vector<FunctionParameter> params){
    for(FunctionParameter &p:params){
        add_variable(p.type,std::make_shared<Parser::VariableDefinitionItem>(p.name,0,0));
    }
}

void DefaultFrame::register_function(std::shared_ptr<Function> func){
    if(MAP_HAS(functions,{func->get_name()})){
        auto &m2=functions[func->get_name()];
        if(MAP_HAS(m2,func->get_parameters())){
            throw MyExcept::SyntaxError(func->get_line(),func->get_line(),"Redefining Function "+func->get_name()+"("+FunctionParameter::get_typelist(func->get_parameters())+")");
        }else{
            m2.insert({func->get_parameters(),func});
        }
    }else{
        functions.insert({func->get_name(),{{func->get_parameters(),func}}});
    }
}

void DefaultFrame::add_function(std::shared_ptr<Parser::FunctionDefinition> func,bool global){
    std::shared_ptr<UserFunction> temp(std::make_shared<UserFunction>(this,func,true));
    register_function(temp);
    if(!global)temp->proccess_delayed();//delay code processing until function is registered, fixes recursion
}

void DefaultFrame::add_definition(std::shared_ptr<Parser::Definition> def,bool global,void(*cb)(void*,std::shared_ptr<Parser::VariableDefinitionItem>,std::shared_ptr<Type>,bool),void * arg){
    switch(def->type){
    case Parser::DEFINITION_VAR:{
            std::shared_ptr<Parser::VariableDefinition> vardef(std::static_pointer_cast<Parser::VariableDefinition>(def->def));
            std::shared_ptr<Type> type = Type::from_vartype(this,vardef->type);
            bool vla=false;
            if(std::shared_ptr<ArrayType> at=std::dynamic_pointer_cast<ArrayType>(type)){
                while(at!=nullptr){
                    if(at->is_vla()){
                        vla=true;
                    }else if(at->get_size()<-1){
                        throw MyExcept::SyntaxError(def->line_start,def->line_start,"invalid size for array");
                    }
                    at=std::dynamic_pointer_cast<ArrayType>(at->get_type());
                }
                if(vla&&global){
                    throw MyExcept::SyntaxError(def->line_start,def->line_start,"global VLA arrays not allowed");
                }
            }
            for(std::shared_ptr<Parser::VariableDefinitionItem> var:vardef->variables){
                add_variable(type,var,global);
                if(cb)cb(arg,var,type,vla);
            }
        }
        break;
    case Parser::DEFINITION_FUNC:
        add_function(std::static_pointer_cast<Parser::FunctionDefinition>(def->def),global);
        break;
    case Parser::DEFINITION_STRUCT:
        throw std::runtime_error("structs not supported yet");//TODO struct runtime
    }
}

void DefaultFrame::add_variable(std::shared_ptr<Type> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global){
    if(CHECKPTR(type,VoidType))throw MyExcept::SyntaxError(var->line_start,var->line_start,"variable type can't be void");
    variable_types.insert({var->name,type});
    if(global&&var->value){
        if(var->value->type==Parser::EXPRESSION_TERM){
            std::shared_ptr<Parser::ExpressionTerm> term(std::static_pointer_cast<Parser::ExpressionTerm>(var->value->contents));
            initialize_globals.push_back(vardefitem_to_assignment(var));
        }
    }
}

std::shared_ptr<Struct> DefaultFrame::get_struct(std::string){
    throw std::runtime_error("structs not supported yet");
}

std::shared_ptr<Expression> DefaultFrame::vardefitem_to_assignment(std::shared_ptr<Parser::VariableDefinitionItem> var){
    return Expression::expr_assign_ignore_const(this,var->name,var->value,var->line_start);
}
