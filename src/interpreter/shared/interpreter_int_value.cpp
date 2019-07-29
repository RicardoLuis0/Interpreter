#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

IntValue::IntValue(int i):value(i){}
IntValue::operator int&(){
    return value;
}

int& IntValue::get(){
    return value;
}

std::shared_ptr<Type> IntValue::get_type(){
    return Type::int_type();
}

std::shared_ptr<Value> IntValue::lt(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value<(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::gt(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value>(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::eq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value==(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::neq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value!=((CHECKPTR(other,IntValue))?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::gt_eq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value>=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::lt_eq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value<=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::mod(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value%std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::bitwise_and(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value&std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::bitwise_or(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value|std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::bitwise_xor(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value^std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::logical_and(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value&&std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::logical_or(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value||std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::add(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value+(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::sub(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value-(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::mul(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value*(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::div(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value/(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::assign(std::shared_ptr<Value> &other){
    value=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_add(std::shared_ptr<Value> &other){
    value+=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_sub(std::shared_ptr<Value> &other){
    value-=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_mul(std::shared_ptr<Value> &other){
    value*=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_div(std::shared_ptr<Value> &other){
    value/=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_mod(std::shared_ptr<Value> &other){
    value%=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_bitwise_and(std::shared_ptr<Value> &other){
    value&=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_bitwise_or(std::shared_ptr<Value> &other){
    value|=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_bitwise_xor(std::shared_ptr<Value> &other){
    value^=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

