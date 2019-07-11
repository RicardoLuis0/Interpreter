#include "interpreter_exec_frame.h"

#include "interpreter_util_defines_misc.h"

#include "interpreter_int_variable.h"
#include "interpreter_float_variable.h"
#include "interpreter_string_variable.h"
#include "interpreter_native_function.h"
#include "interpreter_user_function.h"

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
}

std::shared_ptr<Variable> ExecFrame::get_variable(std::string name){
    MAP_GET(variables,name,parent?parent->get_variable(name):nullptr)
}

std::shared_ptr<Function> ExecFrame::get_function(std::string name){
    return defaults->get_function(name);
}

void ExecFrame::set_variable(std::string s,std::shared_ptr<Value> val){
    if(CHECKPTR(val,IntValue)){
        variables[s]=std::make_shared<IntVariable>(s,std::dynamic_pointer_cast<IntValue>(val)->get());
    }else if(CHECKPTR(val,FloatValue)){
        variables[s]=std::make_shared<FloatVariable>(s,std::dynamic_pointer_cast<FloatValue>(val)->get());
    }else if(CHECKPTR(val,StringValue)){
        variables[s]=std::make_shared<StringVariable>(s,std::dynamic_pointer_cast<StringValue>(val)->get());
    }
}

void ExecFrame::set_args(std::map<std::string,std::shared_ptr<Value>> args){
   for(std::pair<std::string,std::shared_ptr<Value>> arg:args){
        set_variable(arg.first,arg.second);
    }
}

std::shared_ptr<Value> ExecFrame::fn_call(std::shared_ptr<Function> fn,std::vector<std::shared_ptr<Value>> args){
    if(MAP_HAS(defaults->functions,fn->get_name())&&defaults->functions[fn->get_name()]==fn){
        return fn->call(this,args);
    }else{
        return parent->fn_call(fn,args);
    }
}
