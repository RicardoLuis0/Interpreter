#include "interpreter_default_frame.h"

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

std::shared_ptr<Function> DefaultFrame::get_function(std::string name){
    MAP_GET(functions,name,parent?parent->get_function(name):nullptr)
}

void DefaultFrame::add_parameters(std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> params){
    for(std::shared_ptr<Parser::FunctionDefinitionParameter> p:params){
        add_variable(p->type,std::make_shared<Parser::VariableDefinitionItem>(p->name));
    }
}

void DefaultFrame::register_function(std::shared_ptr<Function> func){
    if(MAP_HAS(functions,func->get_name())){
        throw std::runtime_error("Redefining Function "+func->get_name());
    }else{
        functions.insert({func->get_name(),func});
    }
}

void DefaultFrame::add_function(std::shared_ptr<Parser::FunctionDefinition> func){
    register_function(std::make_shared<UserFunction>(this,func));
}

void DefaultFrame::add_definition(std::shared_ptr<Parser::Definition> def,bool global,void(*cb)(void*,std::shared_ptr<Parser::VariableDefinitionItem>),void * arg){
    switch(def->type){
    case Parser::DEFINITION_VAR:{
            std::shared_ptr<Parser::VariableDefinition> vars(std::static_pointer_cast<Parser::VariableDefinition>(def->def));
            for(std::shared_ptr<Parser::VariableDefinitionItem> var:vars->variables){
                add_variable(vars->type,var,global);
                if(cb&&var->value)cb(arg,var);
            }
        }
        break;
    case Parser::DEFINITION_FUNC:
        add_function(std::static_pointer_cast<Parser::FunctionDefinition>(def->def));
        break;
    }
}

void DefaultFrame::add_variable(std::shared_ptr<Parser::VarType> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global){
    if(type->type!=Parser::VARTYPE_PRIMITIVE){
        throw std::runtime_error("variables must be a primitive type");
    }
    if(var->value){
        if(var->value->type==Parser::EXPRESSION_TERM){
            std::shared_ptr<Parser::ExpressionTerm> term(std::static_pointer_cast<Parser::ExpressionTerm>(var->value->contents));
            switch(term->type){
            case Parser::EXPRESSION_TERM_LITERAL_INT:
                switch(type->primitive){
                case Parser::PRIMITIVE_INT:
                    variable_defaults.insert({var->name,std::make_shared<IntVariable>(var->name,std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer())});
                    break;
                case Parser::PRIMITIVE_FLOAT:
                    variable_defaults.insert({var->name,std::make_shared<FloatVariable>(var->name,std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer())});
                    break;
                case Parser::PRIMITIVE_STRING:
                    throw std::runtime_error("cannot assign string to number");
                    break;
                case Parser::PRIMITIVE_INVALID:
                    throw std::runtime_error("invalid primitive type");
                }
                break;
            case Parser::EXPRESSION_TERM_LITERAL_FLOAT:
                switch(type->primitive){
                case Parser::PRIMITIVE_INT:
                    variable_defaults.insert({var->name,std::make_shared<IntVariable>(var->name,std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float())});
                    break;
                case Parser::PRIMITIVE_FLOAT:
                    variable_defaults.insert({var->name,std::make_shared<FloatVariable>(var->name,std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float())});
                    break;
                case Parser::PRIMITIVE_STRING:
                    throw std::runtime_error("cannot assign string to number");
                    break;
                case Parser::PRIMITIVE_INVALID:
                    throw std::runtime_error("invalid primitive type");
                }
                break;
            case Parser::EXPRESSION_TERM_LITERAL_STRING:
                switch(type->primitive){
                case Parser::PRIMITIVE_INT:
                case Parser::PRIMITIVE_FLOAT:
                    throw std::runtime_error("cannot assign number to string");
                    break;
                case Parser::PRIMITIVE_STRING:
                    variable_defaults.insert({var->name,std::make_shared<StringVariable>(var->name,std::static_pointer_cast<Lexer::StringToken>(term->contents_t)->get_string())});
                    break;
                case Parser::PRIMITIVE_INVALID:
                    throw std::runtime_error("invalid primitive type");
                }
                break;
            default:
                if(global)throw std::runtime_error("global variables can only be initiated to literals");
                else goto default_val;
            }
        }
    }else{
    default_val:
        switch(type->primitive){
        case Parser::PRIMITIVE_INT:
            variable_defaults.insert({var->name,std::make_shared<IntVariable>(var->name,0)});
            break;
        case Parser::PRIMITIVE_FLOAT:
            variable_defaults.insert({var->name,std::make_shared<FloatVariable>(var->name,0)});
            break;
        case Parser::PRIMITIVE_STRING:
            variable_defaults.insert({var->name,std::make_shared<StringVariable>(var->name,"")});
            break;
        case Parser::PRIMITIVE_INVALID:
            throw std::runtime_error("invalid primitive type");
        }
    }
}
