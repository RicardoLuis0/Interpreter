#include "Interpreter/TypeType.h"
#include "symbols_keywords.h"
#include "Interpreter/Variable.h"
#include "Interpreter/AnyType.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/DummyValue.h"
#include "Interpreter/DummyVariable.h"
#include "Interpreter/TypeValue.h"
#include "Interpreter/TypeVariable.h"
#include "MyExcept/MyExcept.h"

using namespace Interpreter;

TypeType::TypeType(bool c):Type(c){
}

std::shared_ptr<Type> TypeType::change_const(std::shared_ptr<Type> self,bool new_const){
    return Type::type_type(new_const);
}

std::shared_ptr<Value> TypeType::make_value(std::shared_ptr<Type> self) {
    return std::make_shared<TypeValue>(Type::any_type());
}

std::shared_ptr<Variable> TypeType::make_variable(std::shared_ptr<Type> self,std::string name) {
    return std::make_shared<TypeVariable>(name,Type::any_type());
}

bool TypeType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other) {
    return CHECKPTR(other,TypeType)||Type::is(self,other);
}

std::string TypeType::get_name() {
    return is_const?"const type":"type";
}

std::shared_ptr<Value> TypeType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end) {
    check_variable_assignment(op,self,line_start,line_end);
    switch(op){
    case SYMBOL_NOT_EQUALS:
    case SYMBOL_EQUALS:
        if(other->get_type()->allows_implicit_cast(other->get_type(),Type::type_type())){
            return std::make_shared<DummyValue>(Type::int_type());
        }else{
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
    case SYMBOL_ASSIGNMENT:
        if(other->get_type()->allows_implicit_cast(other->get_type(),Type::type_type())){
            return std::make_shared<DummyVariable>(Type::type_type());
        }else{
            throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
        }
    default:
        //OP_UNKNOWN
        throw MyExcept::SyntaxError(line_start,line_end,"incompatible types "+self->get_type()->get_name()+" and "+other->get_type()->get_name()+" for operator '"+get_op_str(op)+"'");
    }
}

std::shared_ptr<Value> TypeType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) {
    if(!other->get_type()->is(other->get_type(),Type::type_type())){
        try{
            other=other->get_type()->cast(other,Type::type_type());//try to cast to int
        }catch(...){
            throw std::runtime_error("Invalid type '"+other->get_type()->get_name()+"' for int operator '"+get_op_str(op)+"'");
        }
    }
    switch(op){
    default:
        throw std::runtime_error("invalid operator '"+get_op_str(op)+"'");
    case SYMBOL_ASSIGNMENT:
        self->assign(other);
        return self;
    case SYMBOL_EQUALS:
        return self->eq(other);
    case SYMBOL_NOT_EQUALS:
        return self->neq(other);
    }
}
