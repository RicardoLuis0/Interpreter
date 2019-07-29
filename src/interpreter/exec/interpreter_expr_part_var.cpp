#include "interpreter_expr_part_var.h"
#include "interpreter_dummy_variable.h"

using namespace Interpreter;

ExprPartVar::ExprPartVar(DefaultFrame * context,std::string s):ident(s){
    if(context->get_variable(ident)==nullptr)throw std::runtime_error("undefined variable "+ident);
    type=context->get_variable(ident)->get_type();
}

std::shared_ptr<Type> ExprPartVar::get_type(){
    return type;
}

std::shared_ptr<Value> ExprPartVar::eval(ExecFrame * context){
    return context->get_variable(ident);
}

std::shared_ptr<Value> ExprPartVar::get_dummy_type(){
    return std::make_shared<DummyVariable>(get_type());
}
