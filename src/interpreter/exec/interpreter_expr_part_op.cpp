#include "interpreter_expr_part_op.h"

using namespace Interpreter;

ExprPartOp::ExprPartOp(int i):op(i){
}

std::shared_ptr<Parser::VarType> ExprPartOp::get_type(std::shared_ptr<DefaultFrame> context){
    throw std::runtime_error("invalid method get_type for ExprPartOp");
}

std::shared_ptr<Value> ExprPartOp::eval(std::shared_ptr<ExecFrame> context){
    throw std::runtime_error("invalid method eval for ExprPartOp");
}
