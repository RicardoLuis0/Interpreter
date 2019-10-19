#include "Interpreter/TypeVariable.h"

using namespace Interpreter;

TypeVariable::TypeVariable(std::string n,std::shared_ptr<Type> t):Variable(n),TypeValue(t){
    
}
