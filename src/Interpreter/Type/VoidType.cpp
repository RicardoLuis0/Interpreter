#include "Interpreter/VoidType.h"
#include "Interpreter/AnyType.h"
#include "Util/InterpreterUtilDefinesMisc.h"

using namespace Interpreter;

std::string VoidType::get_name(){
    return is_const?"const void":"void";
}

VoidType::VoidType(bool c):Type(c){
}

std::shared_ptr<Type> VoidType::change_const(std::shared_ptr<Type> self,bool new_const){
    return Type::void_type(new_const);
}

bool VoidType::is(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return CHECKPTR(other,VoidType)||Type::is(self,other);
}

bool VoidType::allows_implicit_cast(std::shared_ptr<Type> self,std::shared_ptr<Type> other){
    return is(self,other);
}
