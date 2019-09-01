#include "interpreter_expr_part_is.h"
#include "interpreter_int_value.h"
#include "interpreter_type_value.h"

using namespace Interpreter;

ExprPartIs::ExprPartIs(std::shared_ptr<ExprPart> type,std::shared_ptr<ExprPart> value):type_param(type),param(value){
    if(!type_param->get_type()->is(type_param->get_type(),Type::type_type()))throw std::runtime_error("type parameter for 'is' call is not a valid type");
}

std::shared_ptr<Type> ExprPartIs::get_type(){
    return Type::int_type();
}

std::shared_ptr<Value> ExprPartIs::eval(ExecFrame * context){
    std::shared_ptr<Type> type=param->eval(context)->get_type();
    std::shared_ptr<Type> type2=std::dynamic_pointer_cast<TypeValue>(type_param->eval(context))->get();
    return std::make_shared<IntValue>(type->is(type,type2));
}
