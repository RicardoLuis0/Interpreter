#include "interpreter_expr_part_var.h"

using namespace Interpreter;

ExprPartVar::ExprPartVar(std::shared_ptr<DefaultFrame> context,std::string s):ident(s){
    if(context->get_variable(ident)==nullptr)throw std::runtime_error("undefined variable "+ident);
}

std::shared_ptr<Parser::VarType> ExprPartVar::get_type(std::shared_ptr<DefaultFrame> context){
    return context->get_variable(ident)->get_type();
}

std::shared_ptr<Value> ExprPartVar::eval(std::shared_ptr<ExecFrame> context){
    return context->get_variable(ident);
}
