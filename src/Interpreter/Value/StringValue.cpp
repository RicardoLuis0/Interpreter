#include "Interpreter/StringValue.h"
#include "Interpreter/StringVariable.h"
#include "Interpreter/IntValue.h"
#include "Interpreter/CharValue.h"
#include "Util/InterpreterUtilDefinesMisc.h"

using namespace Interpreter;

StringValue::StringValue(std::string s):value(s){}

const std::string & StringValue::getString(){
    return value;
}
StringValue::operator std::string&(){
    return value;
}

std::string& StringValue::get(){
    return value;
}

std::shared_ptr<Type> StringValue::get_type(){
    return Type::string_type();
}

std::shared_ptr<Value> StringValue::clone(){
    return std::make_shared<StringValue>(value);
}

std::shared_ptr<Variable> StringValue::clone_var(std::string new_name){
    return std::make_shared<StringVariable>(new_name,value);
}

std::shared_ptr<Value> StringValue::assign(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,StringValue)){
        if(CHECKPTR(other,CharValue)){
            value=std::dynamic_pointer_cast<CharValue>(other)->get();
        }else{
            throw std::runtime_error("invalid types for operator '='");
        }
    }else{
        value=std::dynamic_pointer_cast<StringValue>(other)->get();
    }
    return nullptr;
}

std::shared_ptr<Value> StringValue::assign_add(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,StringValue)){
        if(CHECKPTR(other,CharValue)){
            value+=std::dynamic_pointer_cast<CharValue>(other)->get();
        }else{
            throw std::runtime_error("invalid types for operator '+='");
        }
    }else{
        value+=std::dynamic_pointer_cast<StringValue>(other)->get();
    }
    return nullptr;
}

std::shared_ptr<Value> StringValue::add(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,StringValue)){
        if(CHECKPTR(other,CharValue)){
            return std::make_shared<StringValue>(value+std::dynamic_pointer_cast<CharValue>(other)->get());
        }else{
            throw std::runtime_error("invalid types for operator '+'");
        }
    }
    return std::make_shared<StringValue>(value+std::dynamic_pointer_cast<StringValue>(other)->get());
}

std::shared_ptr<Value> StringValue::eq(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,StringValue))throw std::runtime_error("invalid types for operator '=='");
    return std::make_shared<IntValue>(std::dynamic_pointer_cast<StringValue>(other)->get()==value);
}

std::shared_ptr<Value> StringValue::neq(std::shared_ptr<Value> &other){
    if(!CHECKPTR(other,StringValue))throw std::runtime_error("invalid types for operator '!='");
    return std::make_shared<IntValue>(std::dynamic_pointer_cast<StringValue>(other)->get()!=value);
}
