#include "Interpreter/PointerVariable.h"
#include "Interpreter/Type.h"

using namespace Interpreter;

PointerVariable::PointerVariable(std::string s,std::shared_ptr<Type> t,std::shared_ptr<Value> v):Variable(s),PointerValue(t,v){
    
}
