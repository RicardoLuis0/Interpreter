#include "interpreter_expr_part_fn_call.h"
#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

ExprPartFnCall::ExprPartFnCall(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::FunctionCall> fn):ident(fn->identifier){
    std::shared_ptr<Function> fnc=context->get_function(ident);
    if(!fnc)throw std::runtime_error("undefined function "+ident);
    std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> params(fnc->get_parameters());
    std::vector<std::shared_ptr<Parser::Expression>> args;
    if(fn->arguments)args=fn->arguments->expression_list;
    if(params.size()!=args.size()){
        if(params.size()>args.size()){
            throw std::runtime_error("too many arguments for function '"+fn->identifier+"'");
        }else{
            throw std::runtime_error("too few arguments for function '"+fn->identifier+"'");
        }
    }
    for(size_t i=0;i<params.size();i++){
        arguments.push_back(std::make_shared<Expression>(context,args[i]));
        if(!is_compatible(arguments[i]->get_type(),params[i]->type)){
            throw std::runtime_error("incompatible argument type of "+get_name(arguments[i]->get_type())+" for parameter of type "+get_name(params[i]->type));
        }
    }

}

std::shared_ptr<Parser::VarType> ExprPartFnCall::get_type(std::shared_ptr<DefaultFrame> context){
    return context->get_function(ident)->get_type();
}

std::shared_ptr<Value> ExprPartFnCall::eval(std::shared_ptr<ExecFrame> context){
    std::vector<std::shared_ptr<Value>> args;
    std::shared_ptr<Function> fn=context->get_function(ident);
    std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> params=fn->get_parameters();
    for(size_t i=0;i<params.size();i++){
        args.push_back(arguments[i]->eval(context));
    }
    return context->fn_call(fn,args);
}
