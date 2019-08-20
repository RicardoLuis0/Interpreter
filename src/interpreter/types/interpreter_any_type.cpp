#include "interpreter_any_type.h"
#include "interpreter_any_value.h"
#include "interpreter_any_variable.h"
#include "symbols_keywords.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "my_except.h"

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

std::shared_ptr<Value> AnyType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    check_variable_assignment(op,self,line_start,line_end);
    switch(op){
    default:
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
    }
}

std::shared_ptr<Value> AnyType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    if((op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT)&&!CHECKPTR(self,Variable))throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' only available for variables");
    if(pre){
        if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
            return std::make_shared<DummyVariable>(Type::any_type());
        }else if(op==SYMBOL_PLUS||op==SYMBOL_MINUS){
            return std::make_shared<DummyValue>(Type::any_type());
        }
    }else if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
        return std::make_shared<DummyValue>(Type::any_type());
    }
    throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
}
