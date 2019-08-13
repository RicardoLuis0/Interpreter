#include "interpreter_any_type.h"

using namespace Interpreter;

bool AnyType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return true;
}

std::string AnyType::get_name(){
    return "any";
}

std::shared_ptr<Value> AnyType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    return Type::get_operator_result(op,self,other);
}

std::shared_ptr<Value> AnyType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    return Type::get_unary_operator_result(op,self,pre);
}
