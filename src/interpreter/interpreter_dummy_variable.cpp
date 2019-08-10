#include "interpreter_dummy_variable.h"

using namespace Interpreter;

DummyVariable::DummyVariable(std::shared_ptr<Type> t):Variable("dummy_variable"),DummyValue(t){
}

std::shared_ptr<Value> DummyVariable::clone(){
    throw std::runtime_error("Cannot clone DummyValue");
}
