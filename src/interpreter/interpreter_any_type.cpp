#include "interpreter_any_type.h"

using namespace Interpreter;

bool AnyType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return true;
}

std::string AnyType::get_name(){
    return "any";
}
