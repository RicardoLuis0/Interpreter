#include "interpreter_int_type.h"
#include "symbols_keywords.h"
#include "interpreter_variable.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_float_type.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_float_value.h"
#include "interpreter_int_value.h"
#include "interpreter_int_variable.h"

using namespace Interpreter;

std::string IntType::get_name(){
    return "int";
}

std::shared_ptr<Value> IntType::make_value(std::shared_ptr<Type> self){
    return std::make_shared<IntValue>(0);
}

std::shared_ptr<Variable> IntType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<IntVariable>(name,0);
}

bool IntType::allows_implicit_cast(std::shared_ptr<Type> other){
    return CHECKPTR(other,IntType)||CHECKPTR(other,FloatType);
}

std::shared_ptr<Value> IntType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(CHECKPTR(other,IntType)){
        return self;
    }else if(CHECKPTR(other,FloatType)){
        return std::make_shared<FloatValue>(std::dynamic_pointer_cast<IntValue>(self)->get());
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> IntType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
    case SYMBOL_PERCENT_ASSIGNMENT:
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
    case SYMBOL_PERCENT:
    case SYMBOL_LEFT_SHIFT:
    case SYMBOL_RIGHT_SHIFT:
    case SYMBOL_BITWISE_AND:
    case SYMBOL_BITWISE_OR:
    case SYMBOL_BITWISE_XOR:
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
    case SYMBOL_GREATER:
    case SYMBOL_GREATER_EQUALS:
    case SYMBOL_LOWER:
    case SYMBOL_LOWER_EQUALS:
    case SYMBOL_LOGICAL_AND:
    case SYMBOL_LOGICAL_OR:
        if(std::dynamic_pointer_cast<IntType>(other->get_type())==nullptr){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyValue>(self->get_type());
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
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
    case SYMBOL_PERCENT_ASSIGNMENT:
        if((std::dynamic_pointer_cast<IntType>(other->get_type())==nullptr)&&(std::dynamic_pointer_cast<FloatType>(other->get_type())==nullptr)){
            throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyVariable>(self->get_type());
    default:
        //OP_UNKNOWN
        throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> IntType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    if((op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT)&&!CHECKPTR(self,Variable))throw std::runtime_error("operator '"+get_op_str(op)+"' only available for variables");
    if(pre){
        if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
            return std::make_shared<DummyVariable>(self->get_type());
        }else if(op==SYMBOL_PLUS||op==SYMBOL_MINUS){
            return std::make_shared<DummyValue>(self->get_type());
        }
    }else if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
        return std::make_shared<DummyValue>(self->get_type());
    }
    throw std::runtime_error("operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}

std::shared_ptr<Value> IntType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_LEFT_SHIFT:
    case SYMBOL_RIGHT_SHIFT:
        //TODO left,right shift operators and their assignments
        throw std::runtime_error("unimplemented operator '"+get_op_str(op)+"'");
    case SYMBOL_LOGICAL_AND:
        return self->logical_and(other);
    case SYMBOL_LOGICAL_OR:
        return self->logical_or(other);
    case SYMBOL_BITWISE_AND:
        return self->bitwise_and(other);
    case SYMBOL_BITWISE_OR:
        return self->bitwise_or(other);
    case SYMBOL_BITWISE_XOR:
        return self->bitwise_xor(other);
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
        self->assign_bitwise_xor(other);
        return self;
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
        self->assign_bitwise_or(other);
        return self;
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
        self->assign_bitwise_and(other);
        return self;
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
    case SYMBOL_PERCENT_ASSIGNMENT:
        self->assign_mod(other);
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

std::shared_ptr<Value> IntType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(pre){
        switch(op){
        default:
            throw std::runtime_error("invalid unary pre operator '"+get_op_str(op)+"'");
        case SYMBOL_INCREMENT:
            self->unary_pre_increment();
            return self;
        case SYMBOL_DECREMENT:
            self->unary_pre_decrement();
            return self;
        case SYMBOL_PLUS:
            return self->unary_pre_plus();
        case SYMBOL_MINUS:
            return self->unary_pre_minus();
        case SYMBOL_LOGICAL_NOT:
            return self->unary_pre_logical_not();
        }
    }else{
        switch(op){
        default:
            throw std::runtime_error("invalid unary post operator '"+get_op_str(op)+"'");
        case SYMBOL_INCREMENT:
            return self->unary_post_increment();
        case SYMBOL_DECREMENT:
            return self->unary_post_decrement();
        }
    }
}
