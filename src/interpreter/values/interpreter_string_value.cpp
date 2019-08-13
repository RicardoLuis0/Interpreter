#include "interpreter_string_value.h"

#include "interpreter_int_value.h"

using namespace Interpreter;

StringValue::StringValue(std::string s):value(s){}

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

std::shared_ptr<Value> StringValue::assign(std::shared_ptr<Value> &other){//other can only be string
    value=std::dynamic_pointer_cast<StringValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> StringValue::assign_add(std::shared_ptr<Value> &other){//other can only be string
    value+=std::dynamic_pointer_cast<StringValue>(other)->get();
    return nullptr;
}

std::shared_ptr<Value> StringValue::add(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<StringValue>(value+std::dynamic_pointer_cast<StringValue>(other)->get());
}

std::shared_ptr<Value> StringValue::eq(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<IntValue>(std::dynamic_pointer_cast<StringValue>(other)->get()==value);
}

std::shared_ptr<Value> StringValue::neq(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<IntValue>(std::dynamic_pointer_cast<StringValue>(other)->get()!=value);
}
