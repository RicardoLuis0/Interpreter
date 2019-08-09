#include "interpreter_expr_part_value.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_string_value.h"

using namespace Interpreter;

ExprPartValue::ExprPartValue(std::shared_ptr<Value> v):value(v){
    
}

std::shared_ptr<ExprPartValue> ExprPartValue::from_int(int i){
    return std::make_shared<ExprPartValue>(std::make_shared<IntValue>(i));
}

std::shared_ptr<ExprPartValue> ExprPartValue::from_double(double d){
    return std::make_shared<ExprPartValue>(std::make_shared<FloatValue>(d));
}

/*
ExprPartValue::ExprPartValue(int i):value(std::make_shared<IntValue>(i)){
    
}

ExprPartValue::ExprPartValue(double d):value(std::make_shared<FloatValue>(d)){
    
}
*/
ExprPartValue::ExprPartValue(std::string s):value(std::make_shared<StringValue>(s)){
    
}

std::shared_ptr<Type> ExprPartValue::get_type(){
    return value->get_type();
}

std::shared_ptr<Value> ExprPartValue::eval(ExecFrame * context){
    return value;
}
