#include "Interpreter/PointerVariable.h"
#include "Interpreter/Type.h"

using namespace Interpreter;

PointerVariable::PointerVariable(std::string s,std::shared_ptr<Type> type,std::shared_ptr<Value> value):Variable(s),PointerValue(type,value){
    
}
