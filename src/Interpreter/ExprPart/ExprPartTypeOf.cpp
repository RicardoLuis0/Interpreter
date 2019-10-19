#include "Interpreter/ExprPartTypeOf.h"
#include "Interpreter/TypeValue.h"

using namespace Interpreter;

ExprPartTypeOf::ExprPartTypeOf(std::shared_ptr<ExprPart> value):param(value){
    
}

std::shared_ptr<Type> ExprPartTypeOf::get_type(){
    return Type::type_type();
}

std::shared_ptr<Value> ExprPartTypeOf::eval(ExecFrame * context){
    return std::make_shared<TypeValue>(param->eval(context)->get_type());
}
