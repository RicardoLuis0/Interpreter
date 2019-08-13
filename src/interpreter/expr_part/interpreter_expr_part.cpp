#include "interpreter_expr_part.h"
#include "interpreter_dummy_value.h"

using namespace Interpreter;

std::shared_ptr<Value> ExprPart::get_dummy_type(){
    return std::make_shared<DummyValue>(get_type());
}
