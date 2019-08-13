#include "interpreter_float_variable.h"

using namespace Interpreter;

FloatVariable::FloatVariable(std::string n,double d):Variable(n),FloatValue(d){
    
}

std::shared_ptr<Value> FloatVariable::clone(){
    return std::make_shared<FloatVariable>(name,value);
}
