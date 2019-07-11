#include "interpreter_exec_frame.h"

#include "interpreter_util_defines_misc.h"

#include "interpreter_int_variable.h"
#include "interpreter_float_variable.h"
#include "interpreter_string_variable.h"

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

void ExecFrame::set_args(std::map<std::string,std::shared_ptr<Value>> args){
    //TODO ExecFrame::set_args
}

std::shared_ptr<Value> ExecFrame::fn_call(std::shared_ptr<Function>,std::vector<std::shared_ptr<Value>>){
    //TODO ExecFrame::fn_call
    throw std::runtime_error("unimplemented");
}
