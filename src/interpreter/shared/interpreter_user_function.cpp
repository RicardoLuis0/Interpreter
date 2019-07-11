#include "interpreter_user_function.h"

using namespace Interpreter;

UserFunction::UserFunction(DefaultFrame * p,std::shared_ptr<Parser::FunctionDefinition> func):function(func),frame(std::make_shared<DefaultFrame>(p,this)){
    
}

std::string UserFunction::get_name(){
    return function->name;
}

std::shared_ptr<Parser::VarType> UserFunction::get_type(){
    return function->return_type;
}

std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> UserFunction::get_parameters(){
    return function->parameters;
}
/*
std::shared_ptr<Interpreter_Value> UserFunction::call(std::shared_ptr<Interpreter_ExecFrame> parent_frame,std::map<std::string,std::shared_ptr<Interpreter_Value>> args){
    //TODO UserFunction::call
    throw std::runtime_error("unimplemented");
}
*/
