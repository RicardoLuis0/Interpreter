#include "Interpreter/ExprPartOp.h"
#include "symbols_keywords.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/ExprPartVar.h"

using namespace Interpreter;

ExprPartOp::ExprPartOp(std::shared_ptr<ExprPart> l,int i,std::shared_ptr<ExprPart> r,int line_start,int line_end):left(l),right(r),op(i){
    std::shared_ptr<Value> v1(left->get_dummy_type());
    std::shared_ptr<Value> v2(right->get_dummy_type());
    dummyType=v1->get_type()->get_operator_result(op,v1,v2,line_start,line_end);
}

std::shared_ptr<Type> ExprPartOp::get_type(){
    return dummyType->get_type();
}

std::shared_ptr<Value> ExprPartOp::get_dummy_type(){
    return dummyType;
}

std::shared_ptr<Value> ExprPartOp::eval(ExecFrame * context){
    std::shared_ptr<Value> v1=left->eval(context);
    std::shared_ptr<Value> v2=right->eval(context);
    return v1->get_type()->call_operator(op,v1,v2);
}
