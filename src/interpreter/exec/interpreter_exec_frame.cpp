#include "interpreter_exec_frame.h"

#include "interpreter_util_defines_misc.h"

#include "interpreter_int_variable.h"
#include "interpreter_float_variable.h"
#include "interpreter_string_variable.h"

using namespace Interpreter;

ExecFrame::ExecFrame(ExecFrame * p,DefaultFrame * d):parent(p),defaults(d){
    for(auto vpair:defaults->variable_defaults){
        if(typeid(*vpair.second)==typeid(Int_Variable)){
            std::shared_ptr<Int_Variable> var(std::dynamic_pointer_cast<Int_Variable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<Int_Variable>(var->get_name(),var->get())});
        }else if(typeid(*vpair.second)==typeid(Float_Variable)){
            std::shared_ptr<Float_Variable> var(std::dynamic_pointer_cast<Float_Variable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<Float_Variable>(var->get_name(),var->get())});
        }else if(typeid(*vpair.second)==typeid(String_Variable)){
            std::shared_ptr<String_Variable> var(std::dynamic_pointer_cast<String_Variable>(vpair.second));
            variables.insert({var->get_name(),std::make_shared<String_Variable>(var->get_name(),var->get())});
        }else{
            throw std::runtime_error("unknown variable type in defaults");
        }
    }
}

std::shared_ptr<Variable> ExecFrame::get_variable(std::string name){
    MAP_GET(variables,name,parent?parent->get_variable(name):nullptr)
}

std::shared_ptr<Function_Call> ExecFrame::get_function(std::string name){
    return defaults->get_function(name);
}

void ExecFrame::set_args(std::map<std::string,std::shared_ptr<Interpreter_Value>> args){
    //TODO
}
