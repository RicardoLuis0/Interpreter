#include "interpreter_default_frame.h"

#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

DefaultFrame::DefaultFrame(std::vector<std::shared_ptr<Parser::Definition>> defs){
    //TODO
}

DefaultFrame::DefaultFrame(DefaultFrame * parent,Interpreted_Function_Call * call,std::shared_ptr<Parser::CodeBlock> func_body){
    //TODO
}

DefaultFrame::DefaultFrame(DefaultFrame * parent,std::shared_ptr<Parser::CodeBlock> block){
    //TODO
}

DefaultFrame::DefaultFrame(DefaultFrame * parent){
    //TODO
}

std::shared_ptr<Variable> DefaultFrame::get_variable(std::string name){
    MAP_GET(variable_defaults,name,parent?parent->get_variable(name):nullptr)
}

std::shared_ptr<Function_Call> DefaultFrame::get_function(std::string name){
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
