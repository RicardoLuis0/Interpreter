#include "interpreter_default_frame.h"

#include <algorithm>

#include "interpreter_util_defines_misc.h"

#include "parser_variable_definition.h"
#include "parser_expression_term.h"
#include "interpreter_int_variable.h"
#include "interpreter_float_variable.h"
#include "interpreter_string_variable.h"
#include "lexer_integer_token.h"
#include "lexer_float_token.h"
#include "lexer_string_token.h"
#include "interpreter_user_function.h"
#include "deflib.h"
#include "interpreter_primitive_type.h"
#include "parser_binary_operation.h"
#include "lexer_symbol_token.h"
#include "interpreter_void_type.h"
#include "interpreter_expression.h"
#include "interpreter_array_type.h"
#include "my_except.h"

using namespace Interpreter;

DefaultFrame::DefaultFrame(std::vector<std::shared_ptr<Parser::Definition>> defs):parent(nullptr){
    init_deflib(this);
    for(std::shared_ptr<Parser::Definition> def:defs){
        add_definition(def,true);
    }
}

DefaultFrame::DefaultFrame(DefaultFrame * p,std::shared_ptr<Parser::VariableDefinition> def):parent(p){
    add_definition(std::make_shared<Parser::Definition>(Parser::DEFINITION_VAR,def,def->line_start,def->line_end),true);
}

DefaultFrame::DefaultFrame(DefaultFrame * p,Function * f):parent(p){
    add_parameters(f->get_parameters());
    is_function=true;
    func=f;
}

DefaultFrame::DefaultFrame(DefaultFrame * p):parent(p){
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

void DefaultFrame::add_function(std::shared_ptr<Parser::FunctionDefinition> func){
    if(func->variadic){
        throw MyExcept::SyntaxError(func->line_start,func->line_start,"variadic functions not implemented yet");
    }else{
        std::shared_ptr<UserFunction> temp(std::make_shared<UserFunction>(this,func,true));
        register_function(temp);
        temp->proccess_delayed();//delay code processing until function is registered, fixes recursion
    }
}

void DefaultFrame::add_definition(std::shared_ptr<Parser::Definition> def,bool global,void(*cb)(void*,std::shared_ptr<Parser::VariableDefinitionItem>),void * arg){
    switch(def->type){
    case Parser::DEFINITION_VAR:{
            std::shared_ptr<Parser::VariableDefinition> vardef(std::static_pointer_cast<Parser::VariableDefinition>(def->def));
            std::shared_ptr<Type> type = Type::from_vartype(this,vardef->type);
            if(std::shared_ptr<ArrayType> at=std::dynamic_pointer_cast<ArrayType>(type)){
                while(at!=nullptr){
                    if(at->get_size()<=0){
                        throw MyExcept::SyntaxError(def->line_start,def->line_start,"invalid size for array");
                    }
                    at=std::dynamic_pointer_cast<ArrayType>(at->get_type());
                }
            }
            for(std::shared_ptr<Parser::VariableDefinitionItem> var:vardef->variables){
                add_variable(type,var,global);
                if(cb&&var->value)cb(arg,var);
            }
        }
        break;
    case Parser::DEFINITION_FUNC:
        add_function(std::static_pointer_cast<Parser::FunctionDefinition>(def->def));
        break;
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

std::shared_ptr<Expression> DefaultFrame::vardefitem_to_assignment(std::shared_ptr<Parser::VariableDefinitionItem> var){
    return Expression::expr_assign_ignore_const(this,var->name,var->value,var->line_start);
}
