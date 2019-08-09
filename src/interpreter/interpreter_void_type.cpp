#include "interpreter_void_type.h"
#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

std::shared_ptr<Value> VoidType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) {
    throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
}

std::shared_ptr<Value> VoidType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    throw std::runtime_error("operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}

std::shared_ptr<Value> VoidType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) {
    throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
}

std::shared_ptr<Value> VoidType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    throw std::runtime_error("invalid unary post operator '"+get_op_str(op)+"'");\
}

std::shared_ptr<Value> VoidType::make_value(){
    throw std::runtime_error("cannot make void value");
}

std::shared_ptr<Variable> VoidType::make_variable(std::string name){
    throw std::runtime_error("cannot make void variable");
}
