#include "interpreter_expr_part_cast.h"

using namespace Interpreter;

ExprPartCast::ExprPartCast(std::shared_ptr<Type> type,std::shared_ptr<ExprPart> value):type_param(type),param(value){
    
}

std::shared_ptr<Type> ExprPartCast::get_type(){
    return type_param;
}

std::shared_ptr<Value> ExprPartCast::eval(ExecFrame * context){
    std::shared_ptr<Value> value=param->eval(context);
    return value->get_type()->cast(value,type_param);
}
