#include "interpreter_string_variable.h"

using namespace Interpreter;

StringVariable::StringVariable(std::string n,std::string s):Variable(n),StringValue(s){
    
}

std::shared_ptr<Value> StringVariable::clone(){
    return std::make_shared<StringVariable>(name,value);
}
