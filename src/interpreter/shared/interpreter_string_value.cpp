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

std::shared_ptr<Parser::VarType> StringValue::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING);
}

std::shared_ptr<Value> StringValue::assign(std::shared_ptr<Value> &other){//other can only be string
    value=std::dynamic_pointer_cast<StringValue>(other)->get();
    return std::make_shared<StringValue>(value);
}

std::shared_ptr<Value> StringValue::assign_add(std::shared_ptr<Value> &other){//other can only be string
    value+=std::dynamic_pointer_cast<StringValue>(other)->get();
    return std::make_shared<StringValue>(value);
}

std::shared_ptr<Value> StringValue::add(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<StringValue>(std::dynamic_pointer_cast<StringValue>(other)->get()+value);
}

std::shared_ptr<Value> StringValue::eq(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<IntValue>(std::dynamic_pointer_cast<StringValue>(other)->get()==value);
}

std::shared_ptr<Value> StringValue::neq(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<IntValue>(std::dynamic_pointer_cast<StringValue>(other)->get()!=value);
}
