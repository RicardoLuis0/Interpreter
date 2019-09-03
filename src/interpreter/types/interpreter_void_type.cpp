#include "interpreter_void_type.h"
#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

std::string VoidType::get_name(){
    return "void";
}

VoidType::VoidType(bool c):Type(c){
}

std::shared_ptr<Type> VoidType::change_const(std::shared_ptr<Type> self,bool new_const){
    return Type::void_type(new_const);
}
