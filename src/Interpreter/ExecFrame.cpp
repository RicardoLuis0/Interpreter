#include "Interpreter/ExecFrame.h"

#include "Util/InterpreterUtilDefinesMisc.h"

#include "Interpreter/AnyType.h"
#include "Interpreter/IntVariable.h"
#include "Interpreter/FloatVariable.h"
#include "Interpreter/StringVariable.h"
#include "Interpreter/ArrayVariable.h"
#include "Interpreter/PointerVariable.h"
#include "Interpreter/PointerType.h"
#include "Interpreter/UserFunction.h"
#include "Interpreter/IntType.h"
#include "Interpreter/FloatType.h"
#include "Interpreter/StringType.h"
#include "Interpreter/ArrayType.h"
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

void ExecFrame::set_variable(std::string s,std::shared_ptr<Value> val,std::shared_ptr<Type> t,bool reference){
    if(CHECKPTR(t,AnyType)){
        variables[s]=(reference)?std::dynamic_pointer_cast<Variable>(val):val->clone_var(s);
    }else if(CHECKPTR(t,IntType)){
        variables[s]=(reference&&val->get_type()->is(val->get_type(),t))?std::dynamic_pointer_cast<IntVariable>(val):std::dynamic_pointer_cast<IntValue>(val->get_type()->cast(val,t))->clone_var(s);
    }else if(CHECKPTR(t,FloatType)){
        variables[s]=(reference&&val->get_type()->is(val->get_type(),t))?std::dynamic_pointer_cast<FloatVariable>(val):std::dynamic_pointer_cast<FloatValue>(val->get_type()->cast(val,t))->clone_var(s);
    }else if(CHECKPTR(t,StringType)){
        variables[s]=(reference&&val->get_type()->is(val->get_type(),t))?std::dynamic_pointer_cast<StringVariable>(val):std::dynamic_pointer_cast<StringValue>(val->get_type()->cast(val,t))->clone_var(s);
    }else if(CHECKPTR(t,ArrayType)){
        variables[s]=(reference&&val->get_type()->is(val->get_type(),t))?std::dynamic_pointer_cast<ArrayVariable>(val):std::dynamic_pointer_cast<ArrayValue>(val->get_type()->cast(val,t))->clone_var(s);
    }else if(CHECKPTR(t,PointerType)){
        variables[s]=(reference&&val->get_type()->is(val->get_type(),t))?std::dynamic_pointer_cast<PointerVariable>(val):std::dynamic_pointer_cast<PointerValue>(val->get_type()->cast(val,t))->clone_var(s);
    }else{
        throw std::runtime_error("classes not implemented");
    }
}

void ExecFrame::set_args(std::map<std::string,std::pair<std::shared_ptr<Value>,std::pair<bool,std::shared_ptr<Type>>>> args){
   for(std::pair<std::string,std::pair<std::shared_ptr<Value>,std::pair<bool,std::shared_ptr<Type>>>> arg:args){
        set_variable(arg.first,arg.second.first,arg.second.second.second,arg.second.second.first);
    }
}

std::shared_ptr<Value> ExecFrame::fn_call(std::shared_ptr<Function> fn,std::vector<std::shared_ptr<Value>> args){
    if(defaults->get_function_local(fn->get_name(),fn->get_parameters())){
        return fn->call(this,args);
    }else{
        return parent->fn_call(fn,args);
    }
}
