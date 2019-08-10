#include "interpreter_string_type.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_variable.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_string_value.h"
#include "interpreter_string_variable.h"

using namespace Interpreter;

std::string StringType::get_name(){
    return "string";
}

bool StringType::allows_implicit_cast(std::shared_ptr<Type> other){
    return CHECKPTR(other,StringType);
}

std::shared_ptr<Value> StringType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(CHECKPTR(other,StringType)){
        return self;
    }else{
        return Type::cast(self,other);//throws
    }
}


std::shared_ptr<Value> StringType::make_value(std::shared_ptr<Type> self){
    return std::make_shared<StringValue>("");
}

std::shared_ptr<Variable> StringType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<StringVariable>(name,"");
}

std::shared_ptr<Value> StringType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_ASSIGNMENT:
        if(std::dynamic_pointer_cast<Variable>(self)==nullptr){
            throw std::runtime_error("operator '"+get_op_str(op)+"' only available for variables");
        }
        break;
    }
    switch(op){
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
        if(std::dynamic_pointer_cast<StringType>(other->get_type())==nullptr){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyValue>(Type::int_type());
    case SYMBOL_PLUS:
        if(std::dynamic_pointer_cast<StringType>(other->get_type())==nullptr){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyValue>(self->get_type());
    case SYMBOL_ASSIGNMENT:
    case SYMBOL_PLUS_ASSIGNMENT:
        if(std::dynamic_pointer_cast<StringType>(other->get_type())==nullptr){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyVariable>(self->get_type());
    default:
        //OP_UNKNOWN
        throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> StringType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    throw std::runtime_error("operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}

std::shared_ptr<Value> StringType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    case SYMBOL_PLUS_ASSIGNMENT:
        self->assign_add(other);
        return self;
    case SYMBOL_ASSIGNMENT:
        self->assign(other);
        return self;
    case SYMBOL_EQUALS:
        return self->eq(other);
    case SYMBOL_NOT_EQUALS:
        return self->neq(other);
    case SYMBOL_PLUS:
        return self->add(other);
    }
}

std::shared_ptr<Value> StringType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    throw std::runtime_error("invalid unary post operator '"+get_op_str(op)+"'");\
}
