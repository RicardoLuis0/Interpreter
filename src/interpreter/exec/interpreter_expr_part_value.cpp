#include "interpreter_expr_part_value.h"
#include "interpreter_int_value.h"
#include "interpreter_float_value.h"
#include "interpreter_string_value.h"

using namespace Interpreter;

ExprPartValue::ExprPartValue(int i):value(std::make_shared<IntValue>(i)){
    
}

ExprPartValue::ExprPartValue(double d):value(std::make_shared<FloatValue>(d)){
    
}

ExprPartValue::ExprPartValue(std::string s):value(std::make_shared<StringValue>(s)){
    
}

std::shared_ptr<Parser::VarType> ExprPartValue::get_type(std::shared_ptr<DefaultFrame> context){
    return value->get_type();
}

std::shared_ptr<Value> ExprPartValue::eval(std::shared_ptr<ExecFrame> context){
    return value;
}
