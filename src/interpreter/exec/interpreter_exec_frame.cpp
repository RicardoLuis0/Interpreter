#include "interpreter_exec_frame.h"

#include "interpreter_util_defines_misc.h"

#include "interpreter_int_variable.h"
#include "interpreter_float_variable.h"
#include "interpreter_string_variable.h"
#include "interpreter_user_function.h"
#include "interpreter_int_type.h"
#include "interpreter_expression.h"

using namespace Interpreter;

ExecFrame::ExecFrame(ExecFrame * p,DefaultFrame * d):parent(p),defaults(d){
    for(auto vpair:defaults->variable_defaults){
        if(typeid(*vpair.second)==typeid(IntVariable)){
            std::shared_ptr<IntVariable> var(std::dynamic_pointer_cast<IntVariable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<IntVariable>(var->get_name(),var->get())});
        }else if(typeid(*vpair.second)==typeid(FloatVariable)){
            std::shared_ptr<FloatVariable> var(std::dynamic_pointer_cast<FloatVariable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<FloatVariable>(var->get_name(),var->get())});
        }else if(typeid(*vpair.second)==typeid(StringVariable)){
            std::shared_ptr<StringVariable> var(std::dynamic_pointer_cast<StringVariable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<StringVariable>(var->get_name(),var->get())});
        }else{
            throw std::runtime_error("unknown variable type in defaults");
        }
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
    if(CHECKPTR(val,IntValue)){
        if(CHECKPTR(t,IntType)){
            variables[s]=std::make_shared<IntVariable>(s,std::dynamic_pointer_cast<IntValue>(val)->get());
        }else{
            variables[s]=std::make_shared<FloatVariable>(s,std::dynamic_pointer_cast<IntValue>(val)->get());
        }
    }else if(CHECKPTR(val,FloatValue)){
        if(CHECKPTR(t,IntType)){
            variables[s]=std::make_shared<IntVariable>(s,std::dynamic_pointer_cast<FloatValue>(val)->get());
        }else{
            variables[s]=std::make_shared<FloatVariable>(s,std::dynamic_pointer_cast<FloatValue>(val)->get());
        }
    }else if(CHECKPTR(val,StringValue)){
        variables[s]=std::make_shared<StringVariable>(s,std::dynamic_pointer_cast<StringValue>(val)->get());
    }
}

void ExecFrame::set_args(std::map<std::string,std::pair<std::shared_ptr<Value>,std::pair<bool,std::shared_ptr<Type>>>> args){
   for(std::pair<std::string,std::pair<std::shared_ptr<Value>,std::pair<bool,std::shared_ptr<Type>>>> arg:args){
        if(arg.second.second.first){
            if(CHECKPTR(arg.second.first,Variable)){
                variables[arg.first]=std::dynamic_pointer_cast<Variable>(arg.second.first);
                continue;
            }
            //intentional fallthrough
        }
        set_variable(arg.first,arg.second.first,arg.second.second.second);
    }
}

std::shared_ptr<Value> ExecFrame::fn_call(std::shared_ptr<Function> fn,std::vector<std::shared_ptr<Value>> args){
    if(defaults->get_function_local(fn->get_name(),fn->get_parameters())){
        return fn->call(this,args);
    }else{
        return parent->fn_call(fn,args);
    }
}
