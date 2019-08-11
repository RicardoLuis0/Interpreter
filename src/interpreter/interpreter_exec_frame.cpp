#include "interpreter_exec_frame.h"

#include "interpreter_util_defines_misc.h"

#include "interpreter_int_variable.h"
#include "interpreter_float_variable.h"
#include "interpreter_string_variable.h"
#include "interpreter_user_function.h"
#include "interpreter_int_type.h"
#include "interpreter_float_type.h"
#include "interpreter_string_type.h"
#include "interpreter_expression.h"

using namespace Interpreter;

ExecFrame::ExecFrame(ExecFrame * p,DefaultFrame * d):parent(p),defaults(d){
    for(auto vpair:defaults->variable_defaults){
        std::shared_ptr<Variable> var=std::dynamic_pointer_cast<Variable>(vpair.second->clone());
        if(!var)throw std::runtime_error("unexpected nullptr");
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
    if(CHECKPTR(t,IntType)){
        variables[s]=(reference&&CHECKPTR(val,IntVariable))?std::dynamic_pointer_cast<IntVariable>(val):std::make_shared<IntVariable>(s,std::dynamic_pointer_cast<IntValue>(val->get_type()->cast(val,t))->get());
    }else if(CHECKPTR(t,FloatType)){
        variables[s]=(reference&&CHECKPTR(val,FloatVariable))?std::dynamic_pointer_cast<FloatVariable>(val):std::make_shared<FloatVariable>(s,std::dynamic_pointer_cast<FloatValue>(val->get_type()->cast(val,t))->get());
    }else if(CHECKPTR(t,StringType)){
        variables[s]=(reference&&CHECKPTR(val,StringVariable))?std::dynamic_pointer_cast<StringVariable>(val):std::make_shared<StringVariable>(s,std::dynamic_pointer_cast<StringValue>(val->get_type()->cast(val,t))->get());
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