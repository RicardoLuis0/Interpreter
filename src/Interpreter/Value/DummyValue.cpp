#include "Interpreter/DummyValue.h"

using namespace Interpreter;

DummyValue::DummyValue(std::shared_ptr<Type> t2):t(t2){
}

std::shared_ptr<class Type> DummyValue::get_type(){
    return t;
}

std::shared_ptr<Value> DummyValue::clone(){
    throw std::runtime_error("Cannot clone DummyValue");
}

std::shared_ptr<Variable> DummyValue::clone_var(std::string new_name){
    throw std::runtime_error("Cannot clone DummyValue");
}
