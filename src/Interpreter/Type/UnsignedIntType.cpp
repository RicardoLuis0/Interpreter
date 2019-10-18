#include "interpreter_unsigned_int_type.h"
#include "symbols_keywords.h"
#include "interpreter_variable.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_float_type.h"
#include "interpreter_int_type.h"
#include "interpreter_char_type.h"
#include "interpreter_unsigned_char_type.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_float_value.h"
#include "interpreter_int_value.h"
#include "interpreter_char_value.h"
#include "interpreter_unsigned_char_value.h"
#include "interpreter_unsigned_int_value.h"
#include "interpreter_unsigned_int_variable.h"
#include "interpreter_any_type.h"
#include "my_except.h"

using namespace Interpreter;

UnsignedIntType::UnsignedIntType(bool c):PrimitiveType(c){
}

std::shared_ptr<Type> UnsignedIntType::change_const(std::shared_ptr<Type> self,bool new_const){
    return Type::unsigned_int_type(new_const);
}

std::string UnsignedIntType::get_name(){
    return "unsigned int";
}

std::shared_ptr<Value> UnsignedIntType::make_value(std::shared_ptr<Type> self){
    return std::make_shared<UnsignedIntValue>(0);
}

std::shared_ptr<Variable> UnsignedIntType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<UnsignedIntVariable>(name,0);
}

bool UnsignedIntType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,UnsignedIntType)||CHECKPTR(other,AnyType);
}

bool UnsignedIntType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,UnsignedCharType)||CHECKPTR(other,CharType)||CHECKPTR(other,IntType)||CHECKPTR(other,FloatType)||is(self,other);
}

std::shared_ptr<Value> UnsignedIntType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }else if(CHECKPTR(other,IntType)){
        return std::make_shared<IntValue>(std::dynamic_pointer_cast<UnsignedIntValue>(self)->get());
    }else if(CHECKPTR(other,FloatType)){
        return std::make_shared<FloatValue>(std::dynamic_pointer_cast<UnsignedIntValue>(self)->get());
    }else if(CHECKPTR(other,CharType)){
        return std::make_shared<CharValue>(std::dynamic_pointer_cast<UnsignedIntValue>(self)->get());
    }else if(CHECKPTR(other,UnsignedCharType)){
        return std::make_shared<UnsignedCharValue>(std::dynamic_pointer_cast<UnsignedIntValue>(self)->get());
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> UnsignedIntType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    check_variable_assignment(op,self,line_start,line_end);
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
        if(other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_int_type())||other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_char_type())){
            return std::make_shared<DummyValue>(Type::unsigned_int_type());
        }else if(other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())||other->get_type()->allows_implicit_cast(other->get_type(),Type::char_type())){
            return std::make_shared<DummyValue>(Type::int_type());
        }else{
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
    case SYMBOL_PLUS:
    case SYMBOL_MINUS:
    case SYMBOL_MULTIPLY:
    case SYMBOL_DIVIDE:
        if(other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_int_type())||other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_char_type())){
            return std::make_shared<DummyValue>(Type::unsigned_int_type());
        }else if(other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())||other->get_type()->allows_implicit_cast(other->get_type(),Type::char_type())){
            return std::make_shared<DummyValue>(Type::int_type());
        }else if(other->get_type()->allows_implicit_cast(other->get_type(),Type::float_type())){
            return std::make_shared<DummyValue>(Type::float_type());
        }else{
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
    case SYMBOL_ASSIGNMENT:
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_MINUS_ASSIGNMENT:
    case SYMBOL_MULTIPLY_ASSIGNMENT:
    case SYMBOL_DIVIDE_ASSIGNMENT:
        if(!(other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())||
             other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_int_type())||
             other->get_type()->allows_implicit_cast(other->get_type(),Type::char_type())||
             other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_char_type())||
             other->get_type()->allows_implicit_cast(other->get_type(),Type::float_type()))){
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyVariable>(Type::unsigned_int_type());
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
    case SYMBOL_PERCENT_ASSIGNMENT:
        if(!(other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())||
             other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_int_type())||
             other->get_type()->allows_implicit_cast(other->get_type(),Type::char_type())||
             other->get_type()->allows_implicit_cast(other->get_type(),Type::unsigned_char_type()))){
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyVariable>(Type::unsigned_int_type());
    default:
        //OP_UNKNOWN
        throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> UnsignedIntType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    if((op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT)&&!CHECKPTR(self,Variable))throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' only available for variables");
    if(pre){
        if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
            return std::make_shared<DummyVariable>(self->get_type());
        }else if(op==SYMBOL_PLUS||op==SYMBOL_MINUS){
            return std::make_shared<DummyValue>(self->get_type());
        }
    }else if(op==SYMBOL_INCREMENT||op==SYMBOL_DECREMENT||op==SYMBOL_LOGICAL_NOT){
        return std::make_shared<DummyValue>(self->get_type());
    }
    return Type::get_unary_operator_result(op,self,pre,line_start,line_end);
}

std::shared_ptr<Value> UnsignedIntType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    switch(op){
    case SYMBOL_PLUS:
    case SYMBOL_MINUS:
    case SYMBOL_MULTIPLY:
    case SYMBOL_DIVIDE:
    case SYMBOL_ASSIGNMENT:
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_MINUS_ASSIGNMENT:
    case SYMBOL_MULTIPLY_ASSIGNMENT:
    case SYMBOL_DIVIDE_ASSIGNMENT:
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
    case SYMBOL_GREATER:
    case SYMBOL_GREATER_EQUALS:
    case SYMBOL_LOWER:
    case SYMBOL_LOWER_EQUALS:
        if(!(other->get_type()->is(other->get_type(),Type::int_type())||
           other->get_type()->is(other->get_type(),Type::unsigned_int_type())||
           other->get_type()->is(other->get_type(),Type::char_type())||
           other->get_type()->is(other->get_type(),Type::unsigned_char_type())||
           other->get_type()->is(other->get_type(),Type::float_type()))){
            try{
                other=other->get_type()->cast(other,Type::unsigned_int_type());//try to cast to unsigned int
            }catch(...){
                try{
                    other=other->get_type()->cast(other,Type::unsigned_char_type());//try to cast to unsigned char
                }catch(...){
                    try{
                        other=other->get_type()->cast(other,Type::char_type());//try to cast to char
                    }catch(...){
                        try{
                            other=other->get_type()->cast(other,Type::int_type());//try to cast to int
                        }catch(...){
                            try{
                                other=other->get_type()->cast(other,Type::float_type());//try to cast to float
                            }catch(...){
                                throw std::runtime_error("Invalid type '"+other->get_type()->get_name()+"' for int operator '"+get_op_str(op)+"'");
                            }
                        }
                    }
                }
            }
        }
        break;
    case SYMBOL_LEFT_SHIFT_ASSIGNMENT:
    case SYMBOL_RIGHT_SHIFT_ASSIGNMENT:
    case SYMBOL_BITWISE_AND_ASSIGNMENT:
    case SYMBOL_BITWISE_OR_ASSIGNMENT:
    case SYMBOL_BITWISE_XOR_ASSIGNMENT:
    case SYMBOL_PERCENT_ASSIGNMENT:
    case SYMBOL_PERCENT:
    case SYMBOL_LEFT_SHIFT:
    case SYMBOL_RIGHT_SHIFT:
    case SYMBOL_BITWISE_AND:
    case SYMBOL_BITWISE_OR:
    case SYMBOL_BITWISE_XOR:
    case SYMBOL_LOGICAL_AND:
    case SYMBOL_LOGICAL_OR:
        //INT
        if(!(other->get_type()->is(other->get_type(),Type::int_type())||
           other->get_type()->is(other->get_type(),Type::unsigned_int_type())||
           other->get_type()->is(other->get_type(),Type::char_type())||
           other->get_type()->is(other->get_type(),Type::unsigned_char_type())||
           other->get_type()->is(other->get_type(),Type::float_type()))){
            try{
                other=other->get_type()->cast(other,Type::unsigned_int_type());//try to cast to unsigned int
            }catch(...){
                try{
                    other=other->get_type()->cast(other,Type::unsigned_char_type());//try to cast to unsigned char
                }catch(...){
                    try{
                        other=other->get_type()->cast(other,Type::char_type());//try to cast to char
                    }catch(...){
                        try{
                            other=other->get_type()->cast(other,Type::int_type());//try to cast to int
                        }catch(...){
                            try{
                                other=other->get_type()->cast(other,Type::float_type());//try to cast to float
                                other=other->get_type()->cast(other,Type::int_type());
                            }catch(...){
                                throw std::runtime_error("Invalid type '"+other->get_type()->get_name()+"' for int operator '"+get_op_str(op)+"'");
                            }
                        }
                    }
                }
            }
        }
        break;
        break;
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    }
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

std::shared_ptr<Value> UnsignedIntType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(pre){
        switch(op){
        default:
            return Type::call_unary_operator(op,self,pre);
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
            return Type::call_unary_operator(op,self,pre);
        case SYMBOL_INCREMENT:
            return self->unary_post_increment();
        case SYMBOL_DECREMENT:
            return self->unary_post_decrement();
        }
    }
}
