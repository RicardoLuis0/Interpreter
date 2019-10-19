#include "Interpreter/Variable.h"

using namespace Interpreter;

Variable::Variable(std::string s):name(s){
    
}

std::string Variable::get_name(){
    return name;
}
