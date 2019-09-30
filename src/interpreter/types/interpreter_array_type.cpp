#include "interpreter_array_type.h"
#include "symbols_keywords.h"
#include "interpreter_variable.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_type.h"
#include "interpreter_float_type.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_array_value.h"
#include "interpreter_array_variable.h"
#include "interpreter_any_type.h"
#include "my_except.h"

using namespace Interpreter;

ArrayType::ArrayType(std::shared_ptr<Type> t,int s,bool c):Type(c),type(t),size(s){
}

std::shared_ptr<Type> ArrayType::change_const(std::shared_ptr<Type> self,bool new_const){
    if(is_const==new_const){
        return self;
    }else{
        return std::make_shared<ArrayType>(type,size,new_const);
    }
}

std::string ArrayType::get_name(){
    return type->get_name()+"["+(size>=0?std::to_string(size):"")+"]";
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
    if(auto other=std::dynamic_pointer_cast<ArrayType>(o)){
        return ((size<=0||other->size<0||other->size==size)&&other->type->is(other->type,type));
    }else if(CHECKPTR(o,AnyType)){
        return true;
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

std::shared_ptr<Value> ArrayType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    switch(op){
    case SYMBOL_SQUARE_BRACKET_OPEN://[] operator
        if(std::dynamic_pointer_cast<IntType>(other->get_type())==nullptr){
            throw MyExcept::SyntaxError(line_start,line_end,"invalid type "+other->get_type()->get_name()+" for operator '[]', expected integer");
        }
        return std::make_shared<DummyVariable>(std::dynamic_pointer_cast<ArrayType>(self->get_type())->get_type());
    default:
        //OP_UNKNOWN/invalid
        throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> ArrayType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    case SYMBOL_SQUARE_BRACKET_OPEN://[] operator
        return self->access_array(other);
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    }
}
