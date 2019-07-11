#include "interpreter_float_value.h"
#include "interpreter_int_value.h"

using namespace Interpreter;

FloatValue::FloatValue(double d):value(d){}

FloatValue::operator double&(){
    return value;
}

double& FloatValue::get(){
    return value;
}

std::shared_ptr<Parser::VarType> FloatValue::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_FLOAT);
}

std::shared_ptr<Value> FloatValue::lt(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value<(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::gt(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value>(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::eq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value==(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::neq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value==(typeid(*other)!=typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::gt_eq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value>=(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::lt_eq(std::shared_ptr<Value> &other){
    return std::make_shared<IntValue>(value<=(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}
std::shared_ptr<Value> FloatValue::add(std::shared_ptr<Value> &other){
    return std::make_shared<FloatValue>(value+(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::sub(std::shared_ptr<Value> &other){
    return std::make_shared<FloatValue>(value-(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::mul(std::shared_ptr<Value> &other){
    return std::make_shared<FloatValue>(value*(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::div(std::shared_ptr<Value> &other){
    return std::make_shared<FloatValue>(value/(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> FloatValue::assign(std::shared_ptr<Value> &other){
    value=(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_add(std::shared_ptr<Value> &other){
    value+=(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_sub(std::shared_ptr<Value> &other){
    value-=(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_mul(std::shared_ptr<Value> &other){
    value*=(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_div(std::shared_ptr<Value> &other){
    value/=(typeid(*other)==typeid(IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}
