#include "interpreter_default_frame.h"

#include <algorithm>

#include "interpreter_util_defines_misc.h"

#include "parser_variable_definition.h"
#include "parser_expression_term.h"
#include "interpreter_int_variable.h"
#include "interpreter_float_variable.h"
#include "interpreter_string_variable.h"
#include "integer_token.h"
#include "float_token.h"
#include "string_token.h"
#include "interpreter_user_function.h"
#include "deflib.h"
#include "interpreter_primitive_type.h"
#include "parser_binary_operation.h"
#include "symbol_token.h"
#include "interpreter_void_type.h"
#include "interpreter_expression.h"

using namespace Interpreter;

DefaultFrame::DefaultFrame(std::vector<std::shared_ptr<Parser::Definition>> defs):parent(nullptr){
    init_deflib(this);
    for(std::shared_ptr<Parser::Definition> def:defs){
        add_definition(def,true);
    }
}

DefaultFrame::DefaultFrame(DefaultFrame * p,Function * func):parent(p){
    add_parameters(func->get_parameters());
}

DefaultFrame::DefaultFrame(DefaultFrame * p):parent(p){
}

std::shared_ptr<Variable> DefaultFrame::get_variable(std::string name){
    MAP_GET(variable_defaults,name,parent?parent->get_variable(name):nullptr)
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
                if(param_types.size()!=p.first.size())return false;
                for(size_t i=0;i<p.first.size();i++){
                    if(!p.first[i].type->allows_implicit_cast(param_types[i].type))return false;
                }
                return true;
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
        add_variable(p.type,std::make_shared<Parser::VariableDefinitionItem>(p.name));
    }
}

void DefaultFrame::register_function(std::shared_ptr<Function> func){
    if(MAP_HAS(functions,{func->get_name()})){
        auto &m2=functions[func->get_name()];
        if(MAP_HAS(m2,func->get_parameters())){
            throw std::runtime_error("Redefining Function "+func->get_name());
        }else{
            m2.insert({func->get_parameters(),func});
        }
    }else{
        functions.insert({func->get_name(),{{func->get_parameters(),func}}});
    }
}

void DefaultFrame::add_function(std::shared_ptr<Parser::FunctionDefinition> func){
    std::shared_ptr<UserFunction> temp(std::make_shared<UserFunction>(this,func,true));
    register_function(temp);
    temp->proccess_delayed();//delay code processing until function is registered, fixes recursion
}

void DefaultFrame::add_definition(std::shared_ptr<Parser::Definition> def,bool global,void(*cb)(void*,std::shared_ptr<Parser::VariableDefinitionItem>),void * arg){
    switch(def->type){
    case Parser::DEFINITION_VAR:{
            std::shared_ptr<Parser::VariableDefinition> vardef(std::static_pointer_cast<Parser::VariableDefinition>(def->def));
            std::shared_ptr<Type> type = Type::from_vartype(this,vardef->type);
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
    if(CHECKPTR(type,VoidType))throw std::runtime_error("variable type can't be void");
    if(global&&var->value){
        if(var->value->type==Parser::EXPRESSION_TERM){
            std::shared_ptr<Parser::ExpressionTerm> term(std::static_pointer_cast<Parser::ExpressionTerm>(var->value->contents));
            initialize_globals.push_back(std::make_shared<Expression>(this,std::make_shared<Parser::Expression>(
            std::make_shared<Parser::BinaryOperation>(
                std::make_shared<Parser::ExpressionTerm>(std::make_shared<Lexer::WordToken>(0,var->name),Parser::EXPRESSION_TERM_IDENTIFIER),
                std::make_shared<Lexer::SymbolToken>(0,get_symbol_data(SYMBOL_ASSIGNMENT)),
                var->value),Parser::EXPRESSION_BINARY_OPERATION)));
        }
    }
    variable_defaults.insert({var->name,type->make_variable(type,var->name)});
}
