#include "interpreter_float_type.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_variable.h"
#include "interpreter_int_type.h"
#include "interpreter_unsigned_int_type.h"
#include "interpreter_char_type.h"
#include "interpreter_unsigned_char_type.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_int_value.h"
#include "interpreter_unsigned_int_value.h"
#include "interpreter_char_value.h"
#include "interpreter_unsigned_char_value.h"
#include "interpreter_float_value.h"
#include "interpreter_float_variable.h"
#include "interpreter_any_type.h"
#include "my_except.h"

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
    return CHECKPTR(other,UnsignedCharType)||CHECKPTR(other,UnsignedIntType)||CHECKPTR(other,CharType)||CHECKPTR(other,IntType)||is(self,other);
}

std::shared_ptr<Value> FloatType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
        return self;
    }else if(CHECKPTR(other,IntType)){
        return std::make_shared<IntValue>(std::dynamic_pointer_cast<IntValue>(self)->get());
    }else if(CHECKPTR(other,UnsignedIntType)){
        return std::make_shared<UnsignedIntValue>(std::dynamic_pointer_cast<IntValue>(self)->get());
    }else if(CHECKPTR(other,CharType)){
        return std::make_shared<CharValue>(std::dynamic_pointer_cast<IntValue>(self)->get());
    }else if(CHECKPTR(other,UnsignedCharType)){
        return std::make_shared<UnsignedCharValue>(std::dynamic_pointer_cast<IntValue>(self)->get());
    }else{
        return Type::cast(self,other);//throws
    }
}

std::shared_ptr<Value> FloatType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    check_variable_assignment(op,self,line_start,line_end);
    switch(op){
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
    case SYMBOL_GREATER:
    case SYMBOL_GREATER_EQUALS:
    case SYMBOL_LOWER:
    case SYMBOL_LOWER_EQUALS:
        if(!other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())&&!other->get_type()->allows_implicit_cast(other->get_type(),Type::float_type())){
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyValue>(Type::int_type());
    case SYMBOL_PLUS:
    case SYMBOL_MINUS:
    case SYMBOL_MULTIPLY:
    case SYMBOL_DIVIDE:
        if(!other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())&&!other->get_type()->allows_implicit_cast(other->get_type(),Type::float_type())){
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyValue>(Type::float_type());
    case SYMBOL_ASSIGNMENT:
    case SYMBOL_PLUS_ASSIGNMENT:
    case SYMBOL_MINUS_ASSIGNMENT:
    case SYMBOL_MULTIPLY_ASSIGNMENT:
    case SYMBOL_DIVIDE_ASSIGNMENT:
        if(!other->get_type()->allows_implicit_cast(other->get_type(),Type::int_type())&&!other->get_type()->allows_implicit_cast(other->get_type(),Type::float_type())){
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
        return std::make_shared<DummyVariable>(Type::float_type());
    default:
        //OP_UNKNOWN
        throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> FloatType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    if(pre&&(op==SYMBOL_PLUS||op==SYMBOL_MINUS)){
        return std::make_shared<DummyValue>(Type::float_type());
    }else{
        throw MyExcept::SyntaxError(line_start,line_end,"operator '"+get_op_str(op)+"' not available for type "+self->get_type()->get_name());
    }
}

std::shared_ptr<Value> FloatType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    try{
        other=other->get_type()->cast(other,Type::float_type());//try to cast to float
    }catch(...){
        try{
            other=other->get_type()->cast(other,Type::int_type());//if that doesn't work, try casting to int and then to float
            other=other->get_type()->cast(other,Type::float_type());
        }catch(...){
            throw std::runtime_error("Invalid type '"+other->get_type()->get_name()+"' for float operator '"+get_op_str(op)+"'");
        }
    }
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
