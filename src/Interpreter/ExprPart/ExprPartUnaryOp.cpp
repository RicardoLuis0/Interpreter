#include "interpreter_expr_part_unary_op.h"
#include "symbols_keywords.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_expr_part_var.h"

using namespace Interpreter;

ExprPartUnaryOp::ExprPartUnaryOp(std::shared_ptr<ExprPart> v,int i,bool p,int line_start,int line_end):val(v),op(i),pre(p){
    dummyType=v->get_type()->get_unary_operator_result(op,v->get_dummy_type(),p,line_start,line_end);
}

std::shared_ptr<Type> ExprPartUnaryOp::get_type(){
    return dummyType->get_type();
}

std::shared_ptr<Value> ExprPartUnaryOp::get_dummy_type(){
    return dummyType;
}

std::shared_ptr<Value> ExprPartUnaryOp::eval(ExecFrame * context){
    std::shared_ptr<Value> v=val->eval(context);
    return v->get_type()->call_unary_operator(op,v,pre);
}
