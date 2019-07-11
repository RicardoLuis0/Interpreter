#include "interpreter_float_value.h"

using namespace Interpreter;

FloatValue::FloatValue(double d):value(d){}

FloatValue::operator double&(){
    return value;
}

double& FloatValue::get(){
    return value;
}

std::shared_ptr<Parser::VarType> FloatValue::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_FLOAT);
}
