#include "interpreter_type_variable.h"

using namespace Interpreter;

TypeVariable::TypeVariable(std::string n,std::shared_ptr<Type> t):Variable(n),TypeValue(t){
    
}
