#include "Interpreter/ReferenceVariable.h"

using namespace Interpreter;

ReferenceVariable::ReferenceVariable(std::string n,std::shared_ptr<ReferenceType> t,std::shared_ptr<Variable> v):Variable(n),type(t),value(v){
    
}

std::shared_ptr<Type> ReferenceVariable::get_type(){
    return type;
}

std::shared_ptr<Value> ReferenceVariable::clone(){
    return value->clone();
}

std::shared_ptr<Variable> ReferenceVariable::clone_var(std::string new_name){
    return value->clone_var(new_name);
}

std::string ReferenceVariable::get_orig_name(){
    return value->get_name();
}

std::shared_ptr<Type> ReferenceVariable::get_orig_type(){
    return type->type;
}

std::shared_ptr<Variable> ReferenceVariable::get_value(){
    return value;
}
