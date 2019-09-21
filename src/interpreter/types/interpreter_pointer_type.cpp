#include "interpreter_pointer_type.h"
#include "symbols_keywords.h"
#include "interpreter_variable.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_int_type.h"
#include "interpreter_float_type.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_pointer_value.h"
#include "interpreter_pointer_variable.h"
#include "interpreter_any_type.h"
#include "my_except.h"

using namespace Interpreter;

PointerType::PointerType(std::shared_ptr<Type> t,bool c):Type(c),type(t){
}

std::shared_ptr<Type> PointerType::change_const(std::shared_ptr<Type> self,bool new_const){
    if(is_const==new_const){
        return self;
    }else{
        return std::make_shared<PointerType>(type,new_const);
    }
}

std::string PointerType::get_name(){
    return "ptr<"+(type?type->get_name():"?")+">";
}

std::shared_ptr<Value> PointerType::make_value(std::shared_ptr<Type> self){
    return std::make_shared<PointerValue>(std::dynamic_pointer_cast<PointerType>(self),nullptr);
}

std::shared_ptr<Variable> PointerType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<PointerVariable>(name,std::dynamic_pointer_cast<PointerType>(self),nullptr);
}

std::shared_ptr<Type> PointerType::get_type(){
    return type;
}

bool PointerType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> o){
    std::shared_ptr<PointerType> other=std::dynamic_pointer_cast<PointerType>(o);
    return (other&&other->type->is(other->type,type))||(CHECKPTR(other,AnyType));
}

bool PointerType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return is(self,other);
}

std::shared_ptr<Value> PointerType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> PointerType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    switch(op){
    case SYMBOL_ASSIGNMENT://= operator
        if(std::dynamic_pointer_cast<PointerType>(other->get_type())==nullptr){
            throw MyExcept::SyntaxError(line_start,line_end,"invalid type "+other->get_type()->get_name()+" for operator '=', expected pointer");
        }else if(other->get_type()->allows_implicit_cast(other->get_type(),self->get_type())){
            return std::make_shared<DummyVariable>(self->get_type());
        }
    default:
        //OP_UNKNOWN/invalid
        throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> PointerType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    if(pre&&op==SYMBOL_MULTIPLY){
        return std::make_shared<DummyVariable>(type);
    }
    return Type::get_unary_operator_result(op,self,pre,line_start,line_end);
}

std::shared_ptr<Value> PointerType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    other=other->get_type()->cast(other,self->get_type());
    switch(op){
    case SYMBOL_ASSIGNMENT://= operator
        std::dynamic_pointer_cast<PointerValue>(self)->get_value()=std::dynamic_pointer_cast<PointerValue>(other)->get_value();
        return self;
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> PointerType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(pre){
        switch(op){
        case SYMBOL_MULTIPLY:
            return std::dynamic_pointer_cast<PointerValue>(self)->get_value();
        default:
            return Type::call_unary_operator(op,self,pre);
        }
    }else{
        return Type::call_unary_operator(op,self,pre);
    }
}
