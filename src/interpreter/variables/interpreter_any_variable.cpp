#include "interpreter_any_variable.h"

using namespace Interpreter;

AnyVariable::AnyVariable(std::string s):Variable(s){
    
}

std::shared_ptr<Value> AnyVariable::clone(){
    throw std::runtime_error("This method (AnyVariable::clone) shouldn't possibly be called");
}
