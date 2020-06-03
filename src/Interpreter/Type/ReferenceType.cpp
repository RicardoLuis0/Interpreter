#include "Interpreter/ReferenceType.h"
#include "symbols_keywords.h"
#include "Interpreter/Variable.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/IntType.h"
#include "Interpreter/IntValue.h"
#include "Interpreter/DummyValue.h"
#include "Interpreter/DummyVariable.h"
#include "Interpreter/PointerValue.h"
#include "Interpreter/PointerVariable.h"
#include "Interpreter/AnyType.h"
#include "Interpreter/ReferenceVariable.h"
#include "MyExcept/MyExcept.h"

using namespace Interpreter;

ReferenceType::ReferenceType(std::shared_ptr<Type> t,bool c):Type(c),type(t){
    if(type==nullptr){
        throw std::runtime_error("Attempting to Construct ReferenceType with null type");
    }
}

std::shared_ptr<Type> ReferenceType::change_const(std::shared_ptr<Type> self,bool new_const){
    if(is_const==new_const){
        return self;
    }else{
        return std::make_shared<ReferenceType>(type,new_const);
    }
}

std::string ReferenceType::get_name(){
    return is_const?"const "+type->get_name()+"&":type->get_name()+"&";
}

std::shared_ptr<Value> ReferenceType::make_value(std::shared_ptr<Type> self){
    throw std::runtime_error("non-variable references not allowed");
}

std::shared_ptr<Variable> ReferenceType::make_variable(std::shared_ptr<Type> self,std::string name){
    return std::make_shared<ReferenceVariable>(name,std::dynamic_pointer_cast<ReferenceType>(self),nullptr);
}

std::shared_ptr<Type> ReferenceType::get_type(){
    return type;
}

bool ReferenceType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> o){
    return type->is(type,o)&&!(o->get_const()&&!self->get_const());//a const type isn't a non-const reference
}

std::shared_ptr<Value> ReferenceType::cast(std::shared_ptr<Value> self,std::shared_ptr<Type> o){
    if(auto sref=std::dynamic_pointer_cast<ReferenceVariable>(self)){
        return sref->value->get_type()->cast(sref->value,o);
    }
    throw std::runtime_error("This shouldn't ever happen");
}

std::shared_ptr<Value> ReferenceType::get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other,int line_start,int line_end){
    if(auto dummy=std::dynamic_pointer_cast<DummyValue>(self)){
        if(auto ref=std::dynamic_pointer_cast<ReferenceType>(dummy->get_type())){
            return type->get_operator_result(op,std::dynamic_pointer_cast<DummyVariable>(self)?std::make_shared<DummyVariable>(ref->type):std::make_shared<DummyValue>(ref->type),other,line_start,line_end);
        }
    }
    throw std::runtime_error("This shouldn't ever happen");
}

std::shared_ptr<Value> ReferenceType::get_unary_operator_result(int op,std::shared_ptr<Value> self,bool pre,int line_start,int line_end){
    if(auto dummy=std::dynamic_pointer_cast<DummyValue>(self)){
        if(auto ref=std::dynamic_pointer_cast<ReferenceType>(dummy->get_type())){
            return type->get_unary_operator_result(op,std::dynamic_pointer_cast<DummyVariable>(self)?std::make_shared<DummyVariable>(ref->type):std::make_shared<DummyValue>(ref->type),pre,line_start,line_end);
        }
    }
    throw std::runtime_error("This shouldn't ever happen");
}

std::shared_ptr<Value> ReferenceType::call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> o){
    if(auto sref=std::dynamic_pointer_cast<ReferenceVariable>(self)){
        return sref->value->get_type()->call_operator(op,sref->value,o);
    }
    throw std::runtime_error("This shouldn't ever happen");
}

std::shared_ptr<Value> ReferenceType::call_unary_operator(int op,std::shared_ptr<Value> self,bool pre){
    if(auto sref=std::dynamic_pointer_cast<ReferenceVariable>(self)){
		return sref->value->get_type()->call_unary_operator(op,sref->value,pre);
    }
    throw std::runtime_error("This shouldn't ever happen");
}
