#include "interpreter_float_type.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_variable.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_float_variable.h"
#include "interpreter_any_type.h"

using namespace Interpreter;

std::string FloatType::get_name(){
    return "float";
}

std::shared_ptr<Value> FloatType::make_value(std::shared_ptr<Type> self){
    return std::make_shared<FloatValue>(0);
}

std::shared_ptr<Variable> FloatType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<FloatVariable>(name,0);
}

bool FloatType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,FloatType)||CHECKPTR(other,AnyType);
}

bool FloatType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,IntType)||is(self,other);
}

std::shared_ptr<Value> FloatType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }else if(CHECKPTR(other,IntType)){
        return std::make_shared<IntValue>(std::dynamic_pointer_cast<FloatValue>(self)->get());
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> FloatType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_MINUS_ASSIGNMENT:
    case SYMBOL_MULTIPLY_ASSIGNMENT:
    case SYMBOL_DIVIDE_ASSIGNMENT:
    case SYMBOL_ASSIGNMENT:
        if(std::dynamic_pointer_cast<Variable>(self)==nullptr){
            throw std::runtime_error("operator '"+get_op_str(op)+"' only available for variables");
        }
        break;
    }
    switch(op){
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
    case SYMBOL_GREATER:
    case SYMBOL_GREATER_EQUALS:
    case SYMBOL_LOWER:
    case SYMBOL_LOWER_EQUALS:
        if((std::dynamic_pointer_cast<IntType>(other->get_type())==nullptr)&&(std::dynamic_pointer_cast<FloatType>(other->get_type())==nullptr)){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyValue>(Type::int_type());
    case SYMBOL_PLUS:
    case SYMBOL_MINUS:
    case SYMBOL_MULTIPLY:
    case SYMBOL_DIVIDE:
        if((std::dynamic_pointer_cast<IntType>(other->get_type())==nullptr)&&(std::dynamic_pointer_cast<FloatType>(other->get_type())==nullptr)){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyValue>(other->get_type());
    case SYMBOL_ASSIGNMENT:
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_MINUS_ASSIGNMENT:
    case SYMBOL_MULTIPLY_ASSIGNMENT:
    case SYMBOL_DIVIDE_ASSIGNMENT:
        if((std::dynamic_pointer_cast<IntType>(other->get_type())==nullptr)&&(std::dynamic_pointer_cast<FloatType>(other->get_type())==nullptr)){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyVariable>(self->get_type());
    default:
        //OP_UNKNOWN
        throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> FloatType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    if(pre&&(op==SYMBOL_PLUS||op==SYMBOL_MINUS)){
        return std::make_shared<DummyValue>(self->get_type());
    }else{
        throw std::runtime_error("operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
    }
}

std::shared_ptr<Value> FloatType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    case SYMBOL_PLUS_ASSIGNMENT:
        self->assign_add(other);
        return self;
    case SYMBOL_MINUS_ASSIGNMENT:
        self->assign_sub(other);
        return self;
    case SYMBOL_MULTIPLY_ASSIGNMENT:
        self->assign_mul(other);
        return self;
    case SYMBOL_DIVIDE_ASSIGNMENT:
        self->assign_div(other);
        return self;
    case SYMBOL_ASSIGNMENT:
        self->assign(other);
        return self;
    case SYMBOL_EQUALS:
        return self->eq(other);
    case SYMBOL_NOT_EQUALS:
        return self->neq(other);
    case SYMBOL_GREATER:
        return self->gt(other);
    case SYMBOL_GREATER_EQUALS:
        return self->gt_eq(other);
    case SYMBOL_LOWER:
        return self->lt(other);
    case SYMBOL_LOWER_EQUALS:
        return self->lt_eq(other);
    case SYMBOL_PLUS:
        return self->add(other);
    case SYMBOL_MINUS:
        return self->sub(other);
    case SYMBOL_MULTIPLY:
        return self->mul(other);
    case SYMBOL_DIVIDE:
        return self->div(other);
    case SYMBOL_PERCENT:
        return self->mod(other);
    }
}

std::shared_ptr<Value> FloatType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(pre){
        switch(op){
        default:
            throw std::runtime_error("invalid unary pre operator '"+get_op_str(op)+"'");\
        case SYMBOL_PLUS:
            return self->unary_pre_plus();
        case SYMBOL_MINUS:
            return self->unary_pre_minus();
        }
    }else{
        throw std::runtime_error("invalid unary post operator '"+get_op_str(op)+"'");\
    }
}
