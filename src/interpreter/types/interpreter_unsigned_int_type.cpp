#include "interpreter_unsigned_int_type.h"
#include "symbols_keywords.h"
#include "interpreter_variable.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_float_type.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_float_value.h"
#include "interpreter_int_value.h"
#include "interpreter_int_variable.h"
#include "interpreter_any_type.h"

using namespace Interpreter;

std::string UnsignedIntType::get_name(){
    return "unsigned int";
}

std::shared_ptr<Value> UnsignedIntType::make_value(std::shared_ptr<Type> self){
    //return std::make_shared<UnsignedIntValue>(0);
    return nullptr;
}

std::shared_ptr<Variable> UnsignedIntType::make_variable(std::shared_ptr<Type> self,std::string name){
    //return std::make_shared<UnsignedIntVariable>(name,0);
    return nullptr;
}

bool UnsignedIntType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,UnsignedIntType)||CHECKPTR(other,AnyType);
}

bool UnsignedIntType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,IntType)||CHECKPTR(other,FloatType)||is(self,other);
}

std::shared_ptr<Value> UnsignedIntType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }else if(CHECKPTR(other,IntType)){
        return std::make_shared<FloatValue>(std::dynamic_pointer_cast<IntValue>(self)->get());
    }else if(CHECKPTR(other,FloatType)){
        return std::make_shared<FloatValue>(std::dynamic_pointer_cast<IntValue>(self)->get());
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> UnsignedIntType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    return nullptr;
}

std::shared_ptr<Value> UnsignedIntType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    return nullptr;
}

std::shared_ptr<Value> UnsignedIntType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    return nullptr;
}

std::shared_ptr<Value> UnsignedIntType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    return nullptr;
}
