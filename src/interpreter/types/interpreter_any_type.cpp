#include "interpreter_any_type.h"
#include "interpreter_any_value.h"
#include "interpreter_any_variable.h"
#include "symbols_keywords.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"

using namespace Interpreter;

bool AnyType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return true;
}

std::string AnyType::get_name(){
    return "any";
}

std::shared_ptr<Value> AnyType::make_value(std::shared_ptr<Type> self){
    return std::make_shared<AnyValue>();
}

std::shared_ptr<Variable> AnyType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<AnyVariable>(name);
}

std::shared_ptr<Value> AnyType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
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
    case SYMBOL_PLUS:
    case SYMBOL_MINUS:
    case SYMBOL_MULTIPLY:
    case SYMBOL_DIVIDE:
        return std::make_shared<DummyValue>(Type::any_type());
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
    case SYMBOL_SQUARE_BRACKET_OPEN:
        return std::make_shared<DummyVariable>(Type::any_type());
    default:
        throw std::runtime_error("incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> AnyType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre){
    if((op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT)&&!CHECKPTR(self,Variable))throw std::runtime_error("operator '"+get_op_str(op)+"' only available for variables");
    if(pre){
        if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
            return std::make_shared<DummyVariable>(Type::any_type());
        }else if(op==SYMBOL_PLUS||op==SYMBOL_MINUS){
            return std::make_shared<DummyValue>(Type::any_type());
        }
    }else if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
        return std::make_shared<DummyValue>(Type::any_type());
    }
    throw std::runtime_error("operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}
