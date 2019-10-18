#include "interpreter_float_value.h"
#include "interpreter_float_variable.h"
#include "interpreter_int_value.h"
#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

FloatValue::FloatValue(double d){
    dvalue=d;
}

FloatValue::operator double&(){
    return dvalue;
}

double FloatValue::getDouble(){
    return dvalue;
}

double& FloatValue::get(){
    return dvalue;
}

std::shared_ptr<Value> FloatValue::clone(){
    return std::make_shared<FloatValue>(dvalue);
}

std::shared_ptr<Variable> FloatValue::clone_var(std::string new_name){
    return std::make_shared<FloatVariable>(new_name,dvalue);
}

std::shared_ptr<Type> FloatValue::get_type(){
    return Type::float_type();
}

std::shared_ptr<Value> FloatValue::lt(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '<'");
    return std::make_shared<IntValue>(dvalue<std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::gt(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '>'");
    return std::make_shared<IntValue>(dvalue>std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::eq(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '=='");
    return std::make_shared<IntValue>(dvalue==std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::neq(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '!='");
    return std::make_shared<IntValue>(dvalue!=std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::gt_eq(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '>='");
    return std::make_shared<IntValue>(dvalue>=std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::lt_eq(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '<='");
    return std::make_shared<IntValue>(dvalue<=std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::add(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '+'");
    return std::make_shared<FloatValue>(dvalue+std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::sub(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '-'");
    return std::make_shared<FloatValue>(dvalue-std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::mul(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '*'");
    return std::make_shared<FloatValue>(dvalue*std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::div(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '/'");
    return std::make_shared<FloatValue>(dvalue/std::dynamic_pointer_cast<FloatValue>(other)->get());
}

std::shared_ptr<Value> FloatValue::assign(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '='");
    dvalue=std::dynamic_pointer_cast<FloatValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_add(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '+='");
    dvalue+=std::dynamic_pointer_cast<FloatValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_sub(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '-='");
    dvalue-=std::dynamic_pointer_cast<FloatValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_mul(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '*='");
    dvalue*=std::dynamic_pointer_cast<FloatValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> FloatValue::assign_div(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,FloatValue))throw std::runtime_error("invalid types for operator '/='");
    dvalue/=std::dynamic_pointer_cast<FloatValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> FloatValue::unary_pre_plus(){
    return std::make_shared<FloatValue>(dvalue);
}

std::shared_ptr<Value> FloatValue::unary_pre_minus(){
    return std::make_shared<FloatValue>(-dvalue);
}
