#include "interpreter_int_variable.h"

using namespace Interpreter;

IntVariable::IntVariable(std::string n,int i):Variable(n),IntValue(i){
    
}

std::shared_ptr<Value> IntVariable::clone(){
    return std::make_shared<IntVariable>(name,value);
}
