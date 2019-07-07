#include "interpreter_int_value.h"

using namespace Interpreter;

Int_Value::Int_Value(int i):value(i){}
Int_Value::operator int&(){
    return value;
}

int& Int_Value::get(){
    return value;
}

std::shared_ptr<Parser::VarType> Int_Value::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_INT);
}

std::shared_ptr<Value> Int_Value::lt(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '<'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::gt(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '>'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '=='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::neq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '!='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::gt_eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '>='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::lt_eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '<='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::mod(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '%'");//TODO Int_Value operator
}
 std::shared_ptr<Value> Int_Value::bitwise_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::bitwise_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '|'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::bitwise_xor(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '^'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::logical_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&&'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::logical_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '||'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::add(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '+'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::sub(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '-'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::mul(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '*'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::div(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '/'");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_add(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '+='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_sub(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '-='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_mul(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '*='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_div(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '/='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_mod(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '%='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_bitwise_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_bitwise_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '|='");//TODO Int_Value operator
}
std::shared_ptr<Value> Int_Value::assign_bitwise_xor(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '^='");//TODO Int_Value operator
}

