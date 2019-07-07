#include "interpreter_value.h"

using namespace Interpreter;

std::shared_ptr<Value> Value::lt(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '<'");
}
std::shared_ptr<Value> Value::gt(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '>'");
}
std::shared_ptr<Value> Value::eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '=='");
}
std::shared_ptr<Value> Value::neq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '!='");
}
std::shared_ptr<Value> Value::gt_eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '>='");
}
std::shared_ptr<Value> Value::lt_eq(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '<='");
}
std::shared_ptr<Value> Value::mod(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '%'");
}
 std::shared_ptr<Value> Value::bitwise_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&'");
}
std::shared_ptr<Value> Value::bitwise_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '|'");
}
std::shared_ptr<Value> Value::bitwise_xor(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '^'");
}
std::shared_ptr<Value> Value::logical_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&&'");
}
std::shared_ptr<Value> Value::logical_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '||'");
}
std::shared_ptr<Value> Value::add(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '+'");
}
std::shared_ptr<Value> Value::sub(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '-'");
}
std::shared_ptr<Value> Value::mul(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '*'");
}
std::shared_ptr<Value> Value::div(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '/'");
}
std::shared_ptr<Value> Value::assign(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '='");
}
std::shared_ptr<Value> Value::assign_add(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '+='");
}
std::shared_ptr<Value> Value::assign_sub(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '-='");
}
std::shared_ptr<Value> Value::assign_mul(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '*='");
}
std::shared_ptr<Value> Value::assign_div(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '/='");
}
std::shared_ptr<Value> Value::assign_mod(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '%='");
}
std::shared_ptr<Value> Value::assign_bitwise_and(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '&='");
}
std::shared_ptr<Value> Value::assign_bitwise_or(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '|='");
}
std::shared_ptr<Value> Value::assign_bitwise_xor(std::shared_ptr<Value>&){
    throw std::runtime_error("unimplemented operator '^='");
}
