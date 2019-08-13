#include "interpreter_any_value.h"
#include "interpreter_type.h"

using namespace Interpreter;

std::shared_ptr<Type> AnyValue::get_type(){
    return Type::any_type();
}

std::shared_ptr<Value> AnyValue::clone(){
    throw std::runtime_error("This method (AnyValue::clone) shouldn't possibly be called");
}
