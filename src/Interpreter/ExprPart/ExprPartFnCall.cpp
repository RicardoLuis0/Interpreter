#include "Interpreter/ExprPartFnCall.h"
#include "Util/InterpreterUtilDefinesMisc.h"
#include "Interpreter/Variable.h"
#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Interpreter;

ExprPartFnCall::ExprPartFnCall(DefaultFrame * context,std::shared_ptr<Parser::FunctionCall> fn):ident(fn->identifier){
    std::vector<FunctionParameter> params;
    if(fn->arguments){
        for(std::shared_ptr<Parser::Expression> arg:fn->arguments->expression_list){
            arguments.push_back(std::make_shared<Expression>(context,arg));
            params.push_back(arguments.back()->get_type());
        }
    }
    param_types=params;
    std::shared_ptr<Function> fnc=context->get_function(ident,params);
    if(!fnc){
        auto vec=context->get_function_variants(ident);
        if(!vec.empty()){
            std::string error="no match for function '"+ident+"("+FunctionParameter::get_typelist(params)+")'\n\ncandidates:\n";
            for(auto &p:vec){
                error+="  "+ident+"("+FunctionParameter::get_typelist(p,true)+")\n";
            }
            throw MyExcept::SyntaxError(fn->line_start,fn->line_end,error);
        }else{
            throw MyExcept::SyntaxError(fn->line_start,fn->line_end,"call to undefined function '"+ident+"'");
        }
    }
    std::vector<FunctionParameter> params2=fnc->get_parameters();
    for(size_t i=0;i<params2.size();i++){//check reference types
        if(params2[i].is_reference){
            if(CHECKPTR(arguments[i]->get_dummy_type(),Variable)){
                if(!(params[i].type->is(params[i].type,params2[i].type)))throw MyExcept::SyntaxError(fn->line_start,fn->line_end,"types "+params[i].type->get_name()+" and "+params2[i].type->get_name()+" don't match for reference argument");
            }else{
                throw MyExcept::SyntaxError(fn->line_start,fn->line_end,"argument for reference must be a variable");
            }
        }
    }
    type=fnc->get_type();
}

std::shared_ptr<Type> ExprPartFnCall::get_type(){
    return type;
}

std::shared_ptr<Value> ExprPartFnCall::eval(ExecFrame * context){
    std::vector<std::shared_ptr<Value>> args;
    std::shared_ptr<Function> fn=context->get_function(ident,param_types);
    for(size_t i=0;i<param_types.size();i++){
        args.push_back(arguments[i]->eval(context));
    }
    return context->fn_call(fn,args);
}
