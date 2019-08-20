#include "interpreter_int_value.h"
#include "interpreter_int_variable.h"
#include "interpreter_float_value.h"
#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

IntValue::IntValue(int i){
    ivalue=i;
}

IntValue::operator int&(){
    return ivalue;
}

int& IntValue::get(){
    return ivalue;
}

std::shared_ptr<Value> IntValue::clone(){
    return std::make_shared<IntValue>(ivalue);
}

std::shared_ptr<Variable> IntValue::clone_var(std::string new_name){
    return std::make_shared<IntVariable>(new_name,ivalue);
}

std::shared_ptr<Type> IntValue::get_type(){
    return Type::int_type();
}

std::shared_ptr<Value> IntValue::lt(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '<'");
    return std::make_shared<IntValue>(ivalue<(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::gt(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '>'");
    return std::make_shared<IntValue>(ivalue>(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::eq(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '=='");
    return std::make_shared<IntValue>(ivalue==(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::neq(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '!='");
    return std::make_shared<IntValue>(ivalue!=((CHECKPTR(other,IntValue))?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::gt_eq(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '>='");
    return std::make_shared<IntValue>(ivalue>=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::lt_eq(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '<='");
    return std::make_shared<IntValue>(ivalue<=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get()));
}

std::shared_ptr<Value> IntValue::mod(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '%'");
    return std::make_shared<IntValue>(ivalue%std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::bitwise_and(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '&'");
    return std::make_shared<IntValue>(ivalue&std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::bitwise_or(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '|'");
    return std::make_shared<IntValue>(ivalue|std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::bitwise_xor(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '^'");
    return std::make_shared<IntValue>(ivalue^std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::logical_and(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '&&'");
    return std::make_shared<IntValue>(ivalue&&std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::logical_or(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '||'");
    return std::make_shared<IntValue>(ivalue||std::dynamic_pointer_cast<IntValue>(other)->get());
}

std::shared_ptr<Value> IntValue::add(std::shared_ptr<Value> &other){
    if(std::shared_ptr<IntValue> ival=std::dynamic_pointer_cast<IntValue>(other)){
        return std::make_shared<IntValue>(ivalue+ival->get());
    }else if(std::shared_ptr<FloatValue> fval=std::dynamic_pointer_cast<FloatValue>(other)){
        return std::make_shared<FloatValue>(ivalue+fval->get());
    }else{
        throw std::runtime_error("invalid types for operator '+'");
    }
}

std::shared_ptr<Value> IntValue::sub(std::shared_ptr<Value> &other){
    if(std::shared_ptr<IntValue> ival=std::dynamic_pointer_cast<IntValue>(other)){
        return std::make_shared<IntValue>(ivalue-ival->get());
    }else if(std::shared_ptr<FloatValue> fval=std::dynamic_pointer_cast<FloatValue>(other)){
        return std::make_shared<FloatValue>(ivalue-fval->get());
    }else{
        throw std::runtime_error("invalid types for operator '-'");
    }
}

std::shared_ptr<Value> IntValue::mul(std::shared_ptr<Value> &other){
    if(std::shared_ptr<IntValue> ival=std::dynamic_pointer_cast<IntValue>(other)){
        return std::make_shared<IntValue>(ivalue*ival->get());
    }else if(std::shared_ptr<FloatValue> fval=std::dynamic_pointer_cast<FloatValue>(other)){
        return std::make_shared<FloatValue>(ivalue*fval->get());
    }else{
        throw std::runtime_error("invalid types for operator '*'");
    }
}

std::shared_ptr<Value> IntValue::div(std::shared_ptr<Value> &other){
    if(std::shared_ptr<IntValue> ival=std::dynamic_pointer_cast<IntValue>(other)){
        return std::make_shared<IntValue>(ivalue/ival->get());
    }else if(std::shared_ptr<FloatValue> fval=std::dynamic_pointer_cast<FloatValue>(other)){
        return std::make_shared<FloatValue>(ivalue/fval->get());
    }else{
        throw std::runtime_error("invalid types for operator '/'");
    }
}
std::shared_ptr<Value> IntValue::assign(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '='");
    ivalue=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_add(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '+='");
    ivalue+=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_sub(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '-='");
    ivalue-=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_mul(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '*='");
    ivalue*=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_div(std::shared_ptr<Value> &other){
    if(!(CHECKPTR(other,IntValue)||CHECKPTR(other,FloatValue)))throw std::runtime_error("invalid types for operator '/='");
    ivalue/=(CHECKPTR(other,IntValue)?std::dynamic_pointer_cast<IntValue>(other)->get():std::dynamic_pointer_cast<FloatValue>(other)->get());
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_mod(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '%='");
    ivalue%=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_bitwise_and(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '&='");
    ivalue&=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_bitwise_or(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '|='");
    ivalue|=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> IntValue::assign_bitwise_xor(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,IntValue))throw std::runtime_error("invalid types for operator '^='");
    ivalue^=std::dynamic_pointer_cast<IntValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> IntValue::unary_pre_plus(){
    return std::make_shared<IntValue>(ivalue);
}

std::shared_ptr<Value> IntValue::unary_pre_minus(){
    return std::make_shared<IntValue>(-ivalue);
}

std::shared_ptr<Value> IntValue::unary_pre_logical_not(){
    return std::make_shared<IntValue>(!ivalue);
}

std::shared_ptr<Value> IntValue::unary_pre_increment(){
    ++ivalue;
    return nullptr;
}

std::shared_ptr<Value> IntValue::unary_pre_decrement(){
    --ivalue;
    return nullptr;
}

std::shared_ptr<Value> IntValue::unary_post_increment(){
    return std::make_shared<IntValue>(ivalue++);
}

std::shared_ptr<Value> IntValue::unary_post_decrement(){
    return std::make_shared<IntValue>(ivalue--);
}
