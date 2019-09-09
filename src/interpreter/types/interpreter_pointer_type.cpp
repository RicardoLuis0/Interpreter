#include "interpreter_pointer_type.h"
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
    return "pointer<"+(type?"?":type->get_name())+">";
}

std::shared_ptr<Value> PointerType::make_value(std::shared_ptr<Type> self){
    //return std::make_shared<PointerValue>(std::dynamic_pointer_cast<PointerType>(self),nullptr);
    throw std::runtime_error("unimplemented");
}

std::shared_ptr<Variable> PointerType::make_variable(std::shared_ptr<Type> self,std::string name){
    //return std::make_shared<PointerVariable>(name,std::dynamic_pointer_cast<PointerType>(self),nullptr);
    throw std::runtime_error("unimplemented");
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

std::shared_ptr<Value> PointerType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}

std::shared_ptr<Value> PointerType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
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
