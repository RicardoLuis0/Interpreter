#include "interpreter_user_function.h"
#include "interpreter_line_result_return.h"
#include "interpreter_util_defines_misc.h"

using namespace Interpreter;

UserFunction::UserFunction(DefaultFrame * p,std::shared_ptr<Parser::FunctionDefinition> func,bool delay):function(func),frame(std::make_shared<DefaultFrame>(p,this)),code(delay?nullptr:std::make_shared<CodeBlock>(this,func->code)){
    
}

void UserFunction::proccess_delayed(){
    if(!code){
        code=std::make_shared<CodeBlock>(this,function->code);
    }
}

std::string UserFunction::get_name(){
    return function->name;
}

std::shared_ptr<Parser::VarType> UserFunction::get_type(){
    return function->return_type;
}

std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> UserFunction::get_parameters(){
    return function->parameters;
}

std::shared_ptr<Value> UserFunction::call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args){
    std::map<std::string,std::shared_ptr<Value>> args_o;
    int i=0;
    if(function->parameters.size()!=args.size()){
        throw std::runtime_error("wrong parameter count");
    }
    for(std::shared_ptr<Parser::FunctionDefinitionParameter> param:function->parameters){
        args_o.insert({param->name,args[i++]});
    }
    std::shared_ptr<ExecFrame> f(std::make_shared<ExecFrame>(parent_frame,frame.get()));
    f->set_args(args_o);
    std::shared_ptr<LineResult> result=code->run(f);
    switch(result->getAction()){
    case ACTION_RETURN:
        {
            std::shared_ptr<Value> retval(std::dynamic_pointer_cast<LineResultReturn>(result)->get());
            if(is_compatible(retval->get_type(),function->return_type)){
                return retval;
            }
        }
    default:
        if(function->return_type->type==Parser::VARTYPE_VOID){
            return nullptr;
        }else{
            throw std::runtime_error("function "+function->name+" missing return");
        }
    }
}
