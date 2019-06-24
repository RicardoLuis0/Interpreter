#include "Interpreter_Test.h"

#define MAP_FIND(map,key)auto iter=map.find(key);if(iter!=map.end())

#define MAP_GET(map,key,other) MAP_FIND(map,key){return iter->second;}else{return other;}

#define MAP_SET(map,key,val,other) MAP_FIND(map,key){iter->second=val;}else{other;}

#define IS(ptr,type) (typeid(*ptr)==typeid(type))

#include <iostream>

#include "parser_expression_term.h"
#include "string_token.h"
#include "integer_token.h"
#include "float_token.h"

using namespace Interpreter;

class Print_Function : public Native_Function_Call{

    std::string get_name() override {
        return "print";
    }

    std::shared_ptr<Parser::VarType> get_type(){
        return std::make_shared<Parser::VarType>(Parser::VARTYPE_VOID);
    }

    std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override {
        return {std::make_shared<Parser::FunctionDefinitionParameter>(std::make_shared<Parser::VarType>(Parser::VARTYPE_MIXED),"var")};
    }

    std::shared_ptr<Interpreter_Variable> call(Interpreter_Frame * parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Variable>> args) override {
        std::shared_ptr<Interpreter_Variable> var=args["var"];
        if(IS(var,Int_Variable)){
            std::cout<<std::to_string(*std::static_pointer_cast<Int_Variable>(var));
        }else if(IS(var,Float_Variable)){
            std::cout<<std::to_string(*std::static_pointer_cast<Float_Variable>(var));
        }else if(IS(var,String_Variable)){
            std::cout<<std::string(*std::static_pointer_cast<String_Variable>(var));
        }
        return nullptr;
    }
};


Interpreter_Code::Interpreter_Code(std::shared_ptr<Parser::CodeBlock> cb):default_frame(std::make_shared<Interpreter_Frame>()){
    for(auto l:cb->lines){
        readLine(l);
    }
}

Interpreter_Code::Interpreter_Code(std::shared_ptr<Parser::Line> l):default_frame(std::make_shared<Interpreter_Frame>()){
    readLine(l);
}

void Interpreter_Code::readLine(std::shared_ptr<Parser::Line> l){
    //TODO
}

std::string Interpreter_Variable::get_name(){
    return name;
}

Int_Variable::operator int&(){
    return value;
}

int& Int_Variable::get(){
    return value;
}

std::shared_ptr<Parser::VarType> Int_Variable::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);
}

Float_Variable::operator double&(){
    return value;
}

double& Float_Variable::get(){
    return value;
}

std::shared_ptr<Parser::VarType> Float_Variable::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_FLOAT);
}

String_Variable::operator std::string&(){
    return value;
}

std::string& String_Variable::get(){
    return value;
}

std::shared_ptr<Parser::VarType> String_Variable::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING);
}

Interpreted_Function_Call::Interpreted_Function_Call(std::shared_ptr<Parser::FunctionDefinition> func):function(func){}

std::string Interpreted_Function_Call::get_name(){
    return function->name;
}

std::shared_ptr<Parser::VarType> Interpreted_Function_Call::get_type(){
    return function->return_type;
}

std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> Interpreted_Function_Call::get_parameters(){
    return function->parameters;
}

std::shared_ptr<Interpreter_Variable> Interpreted_Function_Call::call(Interpreter_Frame * parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Variable>> args){
    //TODO
    return nullptr;
}

Interpreter_Frame::Interpreter_Frame(){}

Interpreter_Frame::Interpreter_Frame(Interpreter_Frame * other_parent,std::shared_ptr<Interpreter_Frame> other):parent(other_parent?:other->parent){
    //TODO
}

Interpreter_Frame::Interpreter_Frame(std::vector<std::shared_ptr<Parser::Definition>> deflist){
    for(std::shared_ptr<Parser::Definition>def:deflist){
        add_definition(def);
    }
}

void Interpreter_Frame::add_definition(std::shared_ptr<Parser::Definition> def){
    switch(def->type){
    case Parser::DEFINITION_VAR:{
            std::shared_ptr<Parser::VariableDefinition> vars(std::static_pointer_cast<Parser::VariableDefinition>(def->def));
            for(std::shared_ptr<Parser::VariableDefinitionItem> var:vars->variables){
                add_variable(vars->type,var);
            }
        }
        break;
    case Parser::DEFINITION_FUNC:
        add_function(std::static_pointer_cast<Parser::FunctionDefinition>(def->def));
        break;
    }
}

void Interpreter_Frame::add_function(std::shared_ptr<Parser::FunctionDefinition> func){
    interpreted_functions.insert({func->name,std::make_shared<Interpreted_Function_Call>(func)});
}

void Interpreter_Frame::add_variable(std::shared_ptr<Parser::VarType> type,std::shared_ptr<Parser::VariableDefinitionItem> var,bool global){
    if(type->type!=Parser::VARTYPE_PRIMITIVE){
        throw std::runtime_error("variables must be a primitive type");
    }
    switch(type->primitive){
    case Parser::PRIMITIVE_INT:
        variables.insert({var->name,std::make_shared<Int_Variable>()});
        break;
    case Parser::PRIMITIVE_FLOAT:
        variables.insert({var->name,std::make_shared<Float_Variable>()});
        break;
    case Parser::PRIMITIVE_STRING:
        variables.insert({var->name,std::make_shared<String_Variable>()});
        break;
    case Parser::PRIMITIVE_INVALID:
        throw std::runtime_error("invalid primitive type");
    }
    if(var->value){
        if(var->value->type==Parser::EXPRESSION_TERM){
            std::shared_ptr<Parser::ExpressionTerm> term(std::static_pointer_cast<Parser::ExpressionTerm>(var->value->contents));
            switch(term->type){
            case Parser::EXPRESSION_TERM_LITERAL_INT:
                switch(type->primitive){
                case Parser::PRIMITIVE_INT:
                    std::static_pointer_cast<Int_Variable>(variables[var->name])->get()=std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer();
                    variable_defaults.insert({var->name,std::make_shared<Int_Variable>(*std::static_pointer_cast<Int_Variable>(variables[var->name]))});
                    break;
                case Parser::PRIMITIVE_FLOAT:
                    std::static_pointer_cast<Float_Variable>(variables[var->name])->get()=std::static_pointer_cast<Lexer::IntegerToken>(term->contents_t)->get_integer();
                    variable_defaults.insert({var->name,std::make_shared<Float_Variable>(*std::static_pointer_cast<Float_Variable>(variables[var->name]))});
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
                    std::static_pointer_cast<Int_Variable>(variables[var->name])->get()=std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float();
                    variable_defaults.insert({var->name,std::make_shared<Int_Variable>(*std::static_pointer_cast<Int_Variable>(variables[var->name]))});
                    break;
                case Parser::PRIMITIVE_FLOAT:
                    std::static_pointer_cast<Float_Variable>(variables[var->name])->get()=std::static_pointer_cast<Lexer::FloatToken>(term->contents_t)->get_float();
                    variable_defaults.insert({var->name,std::make_shared<Float_Variable>(*std::static_pointer_cast<Float_Variable>(variables[var->name]))});
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
                    std::static_pointer_cast<String_Variable>(variables[var->name])->get()=std::static_pointer_cast<Lexer::StringToken>(term->contents_t)->get_string();
                    variable_defaults.insert({var->name,std::make_shared<String_Variable>(*std::static_pointer_cast<String_Variable>(variables[var->name]))});
                    break;
                case Parser::PRIMITIVE_INVALID:
                    throw std::runtime_error("invalid primitive type");
                }
                break;
            default:
                if(global)throw std::runtime_error("global variables can only be initiated to literals");
            }
        }
    }else{
        switch(type->primitive){
        case Parser::PRIMITIVE_INT:
            variable_defaults.insert({var->name,std::make_shared<Int_Variable>(*std::static_pointer_cast<Int_Variable>(variables[var->name]))});
            break;
        case Parser::PRIMITIVE_FLOAT:
            variable_defaults.insert({var->name,std::make_shared<Float_Variable>(*std::static_pointer_cast<Float_Variable>(variables[var->name]))});
            break;
        case Parser::PRIMITIVE_STRING:
            variable_defaults.insert({var->name,std::make_shared<String_Variable>(*std::static_pointer_cast<String_Variable>(variables[var->name]))});
            break;
        case Parser::PRIMITIVE_INVALID:
            throw std::runtime_error("invalid primitive type");
        }
    }
}


std::shared_ptr<Interpreter_Variable> Interpreter_Frame::get_variable(std::string name){
    MAP_GET(variables,name,parent?parent->get_variable(name):nullptr)
}

std::shared_ptr<Function_Call> Interpreter_Frame::get_function(std::string name){
    MAP_FIND(interpreted_functions,name){
        return iter->second;
    }else{
        MAP_FIND(native_functions,name){
            return iter->second;
        }else{
            return parent?parent->get_function(name):nullptr;
        }
    }
}

void Interpreter_Frame::register_native_function(std::shared_ptr<Native_Function_Call> func){
    MAP_FIND(native_functions,func->get_name()){
        iter->second=func;
    }else{
        throw std::runtime_error("Redefining Native Function");
    }
}

Interpreter_Test::Interpreter_Test(std::vector<std::shared_ptr<Parser::Definition>> df):deflist(df){
    
}

void Interpreter_Test::run(std::string entrypoint_name){
    
}

void Interpreter_Test::run(std::shared_ptr<Interpreter_Frame> frame,std::string entrypoint_name){
    std::shared_ptr<Function_Call> entrypoint(frame->get_function(entrypoint_name));
    if(entrypoint){
        if(entrypoint->get_parameters().empty()){
            entrypoint->call(frame.get(),std::map<std::string,std::shared_ptr<Interpreter_Variable>>());
        }else{
            throw std::runtime_error(entrypoint_name+" cannot have parameters");
        }
    }
}

std::shared_ptr<Interpreter_Frame> Interpreter_Test::build_frame(){
    std::shared_ptr<Interpreter_Frame> frame=std::make_shared<Interpreter_Frame>(deflist);
    frame->register_native_function(std::make_shared<Print_Function>());
    return frame;
}

