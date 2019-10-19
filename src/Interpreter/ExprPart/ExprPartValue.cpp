#include "Interpreter/ExprPartValue.h"
#include "Interpreter/IntValue.h"
#include "Interpreter/CharValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/StringValue.h"

using namespace Interpreter;

ExprPartValue::ExprPartValue(std::shared_ptr<Value> v):value(v){
    
}

std::shared_ptr<ExprPartValue> ExprPartValue::from_int(int i){
    return std::make_shared<ExprPartValue>(std::make_shared<IntValue>(i));
}

std::shared_ptr<ExprPartValue> ExprPartValue::from_char(char c){
    return std::make_shared<ExprPartValue>(std::make_shared<CharValue>(c));
}

std::shared_ptr<ExprPartValue> ExprPartValue::from_double(double d){
    return std::make_shared<ExprPartValue>(std::make_shared<FloatValue>(d));
}

ExprPartValue::ExprPartValue(std::string s):value(std::make_shared<StringValue>(s)){
    
}

std::shared_ptr<Type> ExprPartValue::get_type(){
    return value->get_type();
}

std::shared_ptr<Value> ExprPartValue::eval(ExecFrame * context){
    return value;
}
