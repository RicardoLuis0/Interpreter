#include "Interpreter/TypeValue.h"
#include "Interpreter/TypeVariable.h"
#include "Interpreter/TypeType.h"
#include "Interpreter/IntValue.h"

using namespace Interpreter;

TypeValue::TypeValue(std::shared_ptr<Type> t):value(t) {
    
}

const std::string & TypeValue::getString(){
    temp="type<"+value->get_name()+">";
    return temp;
}

std::shared_ptr<Type>& TypeValue::get() {
    return value;
}

std::shared_ptr<Type> TypeValue::get_type() {
    return Type::type_type();
}

std::shared_ptr<Value> TypeValue::clone() {
    return std::make_shared<TypeValue>(value);
}

std::shared_ptr<class Variable> TypeValue::clone_var(std::string new_name) {
    return std::make_shared<TypeVariable>(new_name,value);
}

std::shared_ptr<Value> TypeValue::eq(std::shared_ptr<Value> &other) {
    std::shared_ptr<Type> v=std::dynamic_pointer_cast<TypeValue>(other)->value;
    return std::make_shared<IntValue>(v->is(v,value));
}

std::shared_ptr<Value> TypeValue::neq(std::shared_ptr<Value> &other) {
    std::shared_ptr<Type> v=std::dynamic_pointer_cast<TypeValue>(other)->value;
    return std::make_shared<IntValue>(!v->is(v,value));
}

std::shared_ptr<Value> TypeValue::assign(std::shared_ptr<Value> &other) {
    value=std::dynamic_pointer_cast<TypeValue>(other)->value;
    return nullptr;
}
