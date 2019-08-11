#include "interpreter_array_type.h"
#include "symbols_keywords.h"
#include "interpreter_variable.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_float_type.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_array_value.h"
#include "interpreter_array_variable.h"

using namespace Interpreter;

ArrayType::ArrayType(std::shared_ptr<Type> t,int s):type(t),size(s){
}

std::string ArrayType::get_name(){
    return "array";
}

std::shared_ptr<Value> ArrayType::make_value(std::shared_ptr<Type> self){
    return std::make_shared<ArrayValue>(std::dynamic_pointer_cast<ArrayType>(self));
}

std::shared_ptr<Variable> ArrayType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<ArrayVariable>(name,std::dynamic_pointer_cast<ArrayType>(self));
}


std::shared_ptr<Type> ArrayType::get_type(){
    return type;
}

int ArrayType::get_size(){
    return size;
}

bool ArrayType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> o){
    std::shared_ptr<ArrayType> other=std::dynamic_pointer_cast<ArrayType>(o);
    if(other){
        return ((size<=0||other->size<0||other->size==size)&&other->type->is(other->type,type));
    }else{
        return false;
    }
}

bool ArrayType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return is(self,other);
}

std::shared_ptr<Value> ArrayType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> ArrayType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    case SYMBOL_SQUARE_BRACKET_OPEN://[] operator
        if(std::dynamic_pointer_cast<IntType>(other->get_type())==nullptr){
            throw std::runtime_error("invalid type "+other->get_type()->get_name()+" for operator '[]', expected integer");
        }
        return std::make_shared<DummyVariable>(std::dynamic_pointer_cast<ArrayType>(self->get_type())->get_type());
    default:
        //OP_UNKNOWN/invalid
        throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> ArrayType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    throw std::runtime_error("operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}

std::shared_ptr<Value> ArrayType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    case SYMBOL_SQUARE_BRACKET_OPEN://[] operator
        return self->access_array(other);
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> ArrayType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(pre){
        switch(op){
        default:
            throw std::runtime_error("invalid unary pre operator '"+get_op_str(op)+"'");
        }
    }else{
        switch(op){
        default:
            throw std::runtime_error("invalid unary post operator '"+get_op_str(op)+"'");
        }
    }
}
