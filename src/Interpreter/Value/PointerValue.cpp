#include "Interpreter/PointerValue.h"
#include "Interpreter/PointerVariable.h"
#include "Interpreter/Type.h"
#include "Interpreter/valueToString.h"

using namespace Interpreter;

PointerValue::PointerValue(std::shared_ptr<PointerType> t,std::shared_ptr<Value> v):type(t),value(v){
}

const std::string & PointerValue::getString(){
    temp=(value?"* "+valueToString(value):"(null)");
    return temp;
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
