#include "interpreter_dummy_value.h"

using namespace Interpreter;

DummyValue::DummyValue(std::shared_ptr<Type> t2):t(t2){
}

std::shared_ptr<class Type> DummyValue::get_type(){
    return t;
}