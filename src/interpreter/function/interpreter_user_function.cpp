#include "interpreter_user_function.h"
#include "interpreter_line_result_return.h"
#include "interpreter_util_defines_misc.h"
#include "interpreter_void_type.h"

using namespace Interpreter;

UserFunction::UserFunction(DefaultFrame * p,std::shared_ptr<Parser::FunctionDefinition> func,bool delay):function(func),parameters(build_parameters(p)),frame(std::make_shared<DefaultFrame>(p,this)),code(delay?nullptr:std::make_shared<CodeBlock>(this,func->code)),return_type(Type::from_vartype(p,func->return_type)){
    
}

void UserFunction::proccess_delayed(){
    if(!code){
        code=std::make_shared<CodeBlock>(this,function->code);
    }
}

std::string UserFunction::get_name(){
    return function->name;
}

std::shared_ptr<Type> UserFunction::get_type(){
    return return_type;
}

std::vector<FunctionParameter> UserFunction::get_parameters(){
    return parameters;
}

std::vector<FunctionParameter> UserFunction::build_parameters(DefaultFrame * context){
    return FunctionParameter::from_pfdp(context,function->parameters);
}

int UserFunction::get_line(){
    return function->line_start;
}

std::shared_ptr<Value> UserFunction::call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args){
    std::map<std::string,std::pair<std::shared_ptr<Value>,std::pair<bool,std::shared_ptr<Type>>>> args_o;
    int i=0;
    if(function->parameters.size()!=args.size()){
        throw std::runtime_error("wrong parameter count");
    }
    for(std::shared_ptr<Parser::FunctionDefinitionParameter> param:function->parameters){
        args_o.insert({param->name,{args[i++],{param->is_reference,Type::from_vartype(frame->parent,param->type)}}});
    }
    std::shared_ptr<ExecFrame> f(code->getContext(parent_frame));
    f->set_args(args_o);
    std::shared_ptr<LineResult> result=code->run(f.get());
    switch(result->getAction()){
    case ACTION_RETURN:{
            std::shared_ptr<Value> retval(std::dynamic_pointer_cast<LineResultReturn>(result)->get());
            if(retval){
                if(CHECKPTR(return_type,VoidType)){
                    throw std::runtime_error("void function "+function->name+" returning a value");
                }else{
                    if(retval->get_type()->allows_implicit_cast(retval->get_type(),return_type)){
                        return retval->get_type()->cast(retval,return_type);
                    }else{
                        throw std::runtime_error("function "+function->name+" returning an invalid value type");
                    }
                }
            }else{
                if(CHECKPTR(return_type,VoidType)){
                    return nullptr;
                }else{
                    throw std::runtime_error("function "+function->name+" missing return value");
                }
            }
        }
    default:
        if(CHECKPTR(return_type,VoidType)){
            return nullptr;
        }else{
            throw std::runtime_error("function "+function->name+" missing return value");
        }
    }
}
