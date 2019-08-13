#include "interpreter_any_variable.h"

using namespace Interpreter;

AnyVariable::AnyVariable(std::string s):Variable(s){
    
}

std::shared_ptr<Value> AnyVariable::clone(){
    return std::make_shared<AnyVariable>(name);
}
