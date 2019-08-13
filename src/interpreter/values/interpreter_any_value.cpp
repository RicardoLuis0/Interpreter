#include "interpreter_any_value.h"
#include "interpreter_any_variable.h"
#include "interpreter_type.h"

using namespace Interpreter;

std::shared_ptr<Type> AnyValue::get_type(){
    return Type::any_type();
}

std::shared_ptr<Value> AnyValue::clone(){
    return std::make_shared<AnyValue>();
}

std::shared_ptr<Variable> AnyValue::clone_var(std::string new_name){
    return std::make_shared<AnyVariable>(new_name);
}
