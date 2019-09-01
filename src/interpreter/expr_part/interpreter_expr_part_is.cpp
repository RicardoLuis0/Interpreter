#include "interpreter_expr_part_is.h"
#include "interpreter_int_value.h"

using namespace Interpreter;

ExprPartIs::ExprPartIs(std::shared_ptr<Type> type,std::shared_ptr<ExprPart> value):type_param(type),param(value){
    
}

std::shared_ptr<Type> ExprPartIs::get_type(){
    return Type::int_type();
}

std::shared_ptr<Value> ExprPartIs::eval(ExecFrame * context){
    std::shared_ptr<Type> type=param->eval(context)->get_type();
    return std::make_shared<IntValue>(type->is(type,type_param));
}
