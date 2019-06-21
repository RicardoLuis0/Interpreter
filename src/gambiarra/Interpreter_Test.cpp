#include "Interpreter_Test.h"

#define MAP_FIND(map,key)auto iter=map.find(key);if(iter!=map.end())

#define MAP_GET(map,key,other) MAP_FIND(map,key){return iter->second;}else{return other;}

#define MAP_SET(map,key,val,other) MAP_FIND(map,key){iter->second=val;}else{other;}

using namespace Interpreter;

Interpreter_Frame::Interpreter_Frame(std::shared_ptr<Interpreter_Frame> other){
    
}

Interpreter_Frame::Interpreter_Frame(std::vector<std::shared_ptr<Parser::Definition>> deflist){
    
}

Interpreter_Frame::Interpreter_Frame(std::shared_ptr<Parser::FunctionDefinition> def){
    
}

Interpreter_Frame::Interpreter_Frame(Interpreter_Frame * parent,std::shared_ptr<Parser::CodeBlock> code){
    
}

std::shared_ptr<Parser::VarType> Interpreter_Frame::find_variable_type(std::string name){
    MAP_GET(variable_types,name,parent?parent->find_variable_type(name):nullptr)
}

int Interpreter_Frame::get_int_variable(std::string name){
    MAP_GET(int_values,name,parent?parent->get_int_variable(name):0)
}

void Interpreter_Frame::set_int_variable(std::string name,int val){
    MAP_SET(int_values,name,val,if(parent)parent->set_int_variable(name,val))
}

float Interpreter_Frame::get_float_variable(std::string name){
    MAP_GET(float_values,name,parent?parent->get_float_variable(name):0)
}

void Interpreter_Frame::set_float_variable(std::string name,float val){
    MAP_SET(float_values,name,val,if(parent)parent->set_float_variable(name,val))
}

std::string Interpreter_Frame::get_string_variable(std::string name){
    MAP_GET(string_values,name,parent?parent->get_string_variable(name):"")
}

void Interpreter_Frame::set_string_variable(std::string name,std::string val){
    MAP_SET(string_values,name,val,if(parent)parent->set_string_variable(name,val))
}

std::shared_ptr<Function_Call> Interpreter_Frame::get_function(std::string name){
    MAP_FIND(interpreted_functions,name){
        return iter->second;
    }else{
        MAP_FIND(native_functions,name){
            return iter->second;
        }else{
            return parent?parent->get_function(name):nullptr;
        }
    }
}

Interpreter_Test::Interpreter_Test(std::vector<std::shared_ptr<Parser::Definition>> deflist):global_frame(deflist){}

void run(std::string entrypoint="main"){
    
}

void register_function(std::shared_ptr<Native_Function_Call>){
    
}
