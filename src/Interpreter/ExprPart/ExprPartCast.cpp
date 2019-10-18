#include "interpreter_expr_part_cast.h"
#include "interpreter_type_value.h"

using namespace Interpreter;

ExprPartCast::ExprPartCast(std::shared_ptr<ExprPart> type,std::shared_ptr<ExprPart> value):type_param(type),param(value){
    if(!type_param->get_type()->is(type_param->get_type(),Type::type_type()))throw std::runtime_error("type parameter for 'cast' call is not a valid type");
}

std::shared_ptr<Type> ExprPartCast::get_type(){
    return Type::any_type();
}

std::shared_ptr<Value> ExprPartCast::eval(ExecFrame * context){
    std::shared_ptr<Value> value=param->eval(context);
    std::shared_ptr<Type> type2=std::dynamic_pointer_cast<TypeValue>(type_param->eval(context))->get();
    return value->get_type()->cast(value,type2);
}
