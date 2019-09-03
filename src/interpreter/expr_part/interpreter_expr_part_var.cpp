#include "interpreter_expr_part_var.h"
#include "interpreter_dummy_variable.h"
#include "my_except.h"

using namespace Interpreter;

ExprPartVar::ExprPartVar(DefaultFrame * context,std::string s,int line):type(context->get_variable_type(ident)),ident(s){
    if(type==nullptr)throw MyExcept::SyntaxError(line,line,"undefined variable "+ident);
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
