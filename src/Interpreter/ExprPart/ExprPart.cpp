#include "Interpreter/ExprPart.h"
#include "Interpreter/DummyValue.h"

using namespace Interpreter;

std::shared_ptr<Value> ExprPart::get_dummy_type(){
    return std::make_shared<DummyValue>(get_type());
}
