#include "Interpreter/DummyVariable.h"

using namespace Interpreter;

DummyVariable::DummyVariable(std::shared_ptr<Type> type):Variable("dummy_variable"),DummyValue(type){
}
