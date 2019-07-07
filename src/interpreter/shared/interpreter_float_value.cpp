#include "interpreter_float_value.h"

using namespace Interpreter;

Float_Value::Float_Value(double d):value(d){}

Float_Value::operator double&(){
    return value;
}

double& Float_Value::get(){
    return value;
}

std::shared_ptr<Parser::VarType> Float_Value::get_type(){
    return std::make_shared<Parser::VarType>(Parser::PRIMITIVE_FLOAT);
}
