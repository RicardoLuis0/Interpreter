#include "interpreter_int_value.h"

using namespace Interpreter;

IntValue::IntValue(int i):value(i){}
IntValue::operator int&(){
    return value;
}

int& IntValue::get(){
    return value;
}

std::shared_ptr<Parser::VarType> IntValue::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);
}

//TODO IntValue operators

std::shared_ptr<Value> IntValue::lt(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '<'");
}
std::shared_ptr<Value> IntValue::gt(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '>'");
}
std::shared_ptr<Value> IntValue::eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '=='");
}
std::shared_ptr<Value> IntValue::neq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '!='");
}
std::shared_ptr<Value> IntValue::gt_eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '>='");
}
std::shared_ptr<Value> IntValue::lt_eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '<='");
}
std::shared_ptr<Value> IntValue::mod(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '%'");
}
 std::shared_ptr<Value> IntValue::bitwise_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&'");
}
std::shared_ptr<Value> IntValue::bitwise_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '|'");
}
std::shared_ptr<Value> IntValue::bitwise_xor(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '^'");
}
std::shared_ptr<Value> IntValue::logical_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&&'");
}
std::shared_ptr<Value> IntValue::logical_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '||'");
}
std::shared_ptr<Value> IntValue::add(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '+'");
}
std::shared_ptr<Value> IntValue::sub(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '-'");
}
std::shared_ptr<Value> IntValue::mul(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '*'");
}
std::shared_ptr<Value> IntValue::div(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '/'");
}
std::shared_ptr<Value> IntValue::assign(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '='");
}
std::shared_ptr<Value> IntValue::assign_add(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '+='");
}
std::shared_ptr<Value> IntValue::assign_sub(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '-='");
}
std::shared_ptr<Value> IntValue::assign_mul(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '*='");
}
std::shared_ptr<Value> IntValue::assign_div(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '/='");
}
std::shared_ptr<Value> IntValue::assign_mod(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '%='");
}
std::shared_ptr<Value> IntValue::assign_bitwise_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&='");
}
std::shared_ptr<Value> IntValue::assign_bitwise_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '|='");
}
std::shared_ptr<Value> IntValue::assign_bitwise_xor(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '^='");
}

