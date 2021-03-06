#include "Interpreter/ArrayType.h"
#include "symbols_keywords.h"
#include "Interpreter/Variable.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/IntType.h"
#include "Interpreter/FloatType.h"
#include "Interpreter/DummyValue.h"
#include "Interpreter/DummyVariable.h"
#include "Interpreter/ArrayValue.h"
#include "Interpreter/ArrayVariable.h"
#include "Interpreter/AnyType.h"
#include "Interpreter/IntValue.h"
#include "MyExcept/MyExcept.h"

using namespace Interpreter;

ArrayType::ArrayType(std::shared_ptr<Type> t,int s,bool c):Type(c),type(t),size(s),len_expr(nullptr){
    if(size<-2){
        throw std::runtime_error("invalid array size");
    }
}

ArrayType::ArrayType(std::shared_ptr<Type> t,std::shared_ptr<Expression> expr,bool c):Type(c),type(t),size(-1),len_expr(expr){
    
}

std::shared_ptr<Type> ArrayType::change_const(std::shared_ptr<Type> self,bool new_const){
    if(is_const==new_const){
        return self;
    }else{
        return std::make_shared<ArrayType>(type,size,new_const);
    }
}

std::string ArrayType::get_name(){
    return is_const?"const "+type->get_name()+"["+(size>=0?std::to_string(size):"")+"]":type->get_name()+"["+(size>=0?std::to_string(size):"")+"]";
}

std::shared_ptr<Value> ArrayType::make_value(std::shared_ptr<Type> self){
    if(is_vla())throw std::runtime_error("Trying to instantiate VLA array as non-VLA");
    return std::make_shared<ArrayValue>(std::dynamic_pointer_cast<ArrayType>(self));
}

std::shared_ptr<Variable> ArrayType::make_variable(std::shared_ptr<Type> self,std::string name){
    if(is_vla())throw std::runtime_error("Trying to instantiate VLA array as non-VLA");
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
    }else{
        return Type::is(self,o);
    }
}

bool ArrayType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> o){
    if(auto other=std::dynamic_pointer_cast<ArrayType>(o)){
        return (CHECKPTR(other->type,AnyType)&&(other->size<0||other->size==size))||is(self,o);
    } else {
        return Type::allows_implicit_cast(self,o);
    }
}

std::shared_ptr<Value> ArrayType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> ArrayType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    check_variable_assignment(op,self,line_start,line_end);
    switch(op){
    case SYMBOL_ASSIGNMENT:
        if(other->get_type()->allows_implicit_cast(other->get_type(),self->get_type())){
            return std::make_shared<DummyValue>(self->get_type());
        }else{
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
    case SYMBOL_SQUARE_BRACKET_OPEN://[] operator
        if(!other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())){
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
    case SYMBOL_ASSIGNMENT:
        if(auto arrv=std::dynamic_pointer_cast<ArrayValue>(other->get_type()->cast(other,self->get_type()))){
            auto arrs=std::dynamic_pointer_cast<ArrayValue>(self);
            arrs->array=arrv->clone_array();
        }
        return self;
    case SYMBOL_SQUARE_BRACKET_OPEN://[] operator
        other=other->get_type()->cast(other,Type::int_type());
        return self->access_array(other);
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<ArrayType> ArrayType::build_vla_array_type(ExecFrame * context){
    if(is_vla()){
        auto val=len_expr->eval(context);
        int new_len=std::dynamic_pointer_cast<IntValue>(val->get_type()->cast(val,Type::int_type()))->get();
        if(new_len<0){
            throw std::runtime_error("invalid size for VLA array");
        }
        if(auto arrt=std::dynamic_pointer_cast<ArrayType>(type)){
            if(arrt->is_vla()){
                return std::make_shared<ArrayType>(arrt->build_vla_array_type(context),new_len,is_const);
            }
        }
        return std::make_shared<ArrayType>(type,new_len,is_const);
    }else if(auto arrt=std::dynamic_pointer_cast<ArrayType>(type)){
        return std::make_shared<ArrayType>(arrt->build_vla_array_type(context),size,is_const);
    }else{
        throw std::runtime_error("trying to instantiate a non-VLA array as VLA");
    }
}

bool ArrayType::is_vla(){
    if(size==-1&&len_expr){
        return true;
    }else if(auto arrt=std::dynamic_pointer_cast<ArrayType>(type)){
        return arrt->is_vla();
    }else{
        return false;
    }
}
