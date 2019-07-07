#include "interpreter_string_value.h"

#include "interpreter_int_value.h"

using namespace Interpreter;

String_Value::String_Value(std::string s):value(s){}

String_Value::operator std::string&(){
    return value;
}

std::string& String_Value::get(){
    return value;
}

std::shared_ptr<Parser::VarType> String_Value::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_STRING);
}

std::shared_ptr<Value> String_Value::assign(std::shared_ptr<Value> &other){//other can only be string
    value=std::dynamic_pointer_cast<String_Value>(other)->get();
    return std::make_shared<String_Value>(value);
}

std::shared_ptr<Value> String_Value::assign_add(std::shared_ptr<Value> &other){//other can only be string
    value+=std::dynamic_pointer_cast<String_Value>(other)->get();
    return std::make_shared<String_Value>(value);
}

std::shared_ptr<Value> String_Value::add(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<String_Value>(std::dynamic_pointer_cast<String_Value>(other)->get()+value);
}

std::shared_ptr<Value> String_Value::eq(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<Int_Value>(std::dynamic_pointer_cast<String_Value>(other)->get()==value);
}

std::shared_ptr<Value> String_Value::neq(std::shared_ptr<Value> &other){//other can only be string
    return std::make_shared<Int_Value>(std::dynamic_pointer_cast<String_Value>(other)->get()!=value);
}
