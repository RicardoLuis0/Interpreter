#include "interpreter_pointer_value.h"
#include "interpreter_pointer_variable.h"
#include "interpreter_type.h"

using namespace Interpreter;

PointerValue::PointerValue(std::shared_ptr<Type> t,std::shared_ptr<Value> v):type(t),value(v){
}

std::shared_ptr<Type> PointerValue::get_type(){
    return type;
}

std::shared_ptr<Value>& PointerValue::get_value(){
    return value;
}

std::shared_ptr<Value> PointerValue::clone(){
    return std::make_shared<PointerValue>(type,value);
}

std::shared_ptr<Variable> PointerValue::clone_var(std::string new_name){
    return std::make_shared<PointerVariable>(new_name,type,value);
}
