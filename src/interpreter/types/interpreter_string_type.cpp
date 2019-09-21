#include "interpreter_string_type.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_variable.h"
#include "interpreter_dummy_value.h"
#include "interpreter_dummy_variable.h"
#include "interpreter_string_value.h"
#include "interpreter_string_variable.h"
#include "interpreter_any_type.h"
#include "my_except.h"

using namespace Interpreter;

StringType::StringType(bool c):Type(c){
}

std::shared_ptr<Type> StringType::change_const(std::shared_ptr<Type> self,bool new_const){
    return Type::string_type(new_const);
}

std::string StringType::get_name(){
    return "string";
}

bool StringType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,StringType)||CHECKPTR(other,AnyType);
}

bool StringType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return is(self,other);
}

std::shared_ptr<Value> StringType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> other){
    if(is(self->get_type(),other)){
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

std::shared_ptr<Value> StringType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    check_variable_assignment(op,self,line_start,line_end);
    if(!other->get_type()->allows_implicit_cast(other->get_type(),Type::string_type())){
        throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
    switch(op){
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
        return std::make_shared<DummyValue>(Type::int_type());
    case SYMBOL_PLUS:
        return std::make_shared<DummyValue>(Type::string_type());
    case SYMBOL_ASSIGNMENT:
    case SYMBOL_PLUS_ASSIGNMENT:
        return std::make_shared<DummyVariable>(Type::string_type());
    default:
        //OP_UNKNOWN
        throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> StringType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other){
    try{
        other=other->get_type()->cast(other,Type::string_type());
    }catch(...){
        throw std::runtime_error("Invalid type '"+other->get_type()->get_name()+"' for string operator '"+get_op_str(op)+"'");
    }
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
