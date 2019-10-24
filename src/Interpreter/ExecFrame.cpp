#include "Interpreter/ExecFrame.h"

#include "Util/InterpreterUtilDefinesMisc.h"

#include "Interpreter/ArrayType.h"
#include "Interpreter/Type.h"
#include "Interpreter/Variable.h"
#include "Interpreter/ReferenceType.h"
#include "Interpreter/ReferenceVariable.h"
#include "Interpreter/Expression.h"
#include "MyExcept/MyExcept.h"
#include <typeinfo>

using namespace Interpreter;

ExecFrame::ExecFrame(ExecFrame * p,DefaultFrame * d):parent(p),defaults(d){
    for(std::pair<std::string,std::shared_ptr<Type>> vpair:defaults->variable_types){
        if(auto arr=std::dynamic_pointer_cast<ArrayType>(vpair.second)){
            if(arr->is_vla())continue;
        }
        std::shared_ptr<Variable> var=vpair.second->make_variable(vpair.second,vpair.first);
        if(!var){
            throw std::runtime_error("unexpected nullptr in "+std::string(vpair.second->get_name())+"::make_variable");
        }
        variables.insert({vpair.first,var});
    }
    for(std::shared_ptr<Expression> e:defaults->initialize_globals){
        e->run(this);
    }
}

std::shared_ptr<Variable> ExecFrame::get_variable(std::string name){
    MAP_GET(variables,name,parent?parent->get_variable(name):nullptr)
}

std::shared_ptr<Function> ExecFrame::get_function(std::string name,std::vector<FunctionParameter> param_types){
    return defaults->get_function(name,param_types);
}

void ExecFrame::set_variable(std::string s,std::shared_ptr<Value> val,std::shared_ptr<Type> t){
    if(auto ref=std::dynamic_pointer_cast<ReferenceType>(t)){
        if(auto var=std::dynamic_pointer_cast<Variable>(val)){
            if(var->get_type()->is(var->get_type(),ref->get_type())){
                variables[s]=std::make_shared<ReferenceVariable>(s,ref,var);
				return;
            }
        }
    }else{
        variables[s]=val->clone_var(s);
		return;
    }
    throw std::runtime_error("invalid reference type");
}

void ExecFrame::set_args(std::map<std::string,std::pair<std::shared_ptr<Value>,std::shared_ptr<Type>>> args){
   for(std::pair<std::string,std::pair<std::shared_ptr<Value>,std::shared_ptr<Type>>> arg:args){
        set_variable(arg.first,arg.second.first,arg.second.second);
    }
}

std::shared_ptr<Value> ExecFrame::fn_call(std::shared_ptr<Function> fn,std::vector<std::shared_ptr<Value>> args){
    if(defaults->get_function_local(fn->get_name(),fn->get_parameters())){
        return fn->call(this,args);
    }else{
        return parent->fn_call(fn,args);
    }
}
