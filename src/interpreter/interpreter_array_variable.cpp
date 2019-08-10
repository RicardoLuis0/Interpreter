#include "interpreter_array_variable.h"

using namespace Interpreter;

ArrayVariable::ArrayVariable(std::string n,std::shared_ptr<ArrayType> t):Variable(n),ArrayValue(t){
    
}

ArrayVariable::ArrayVariable(std::string n,std::shared_ptr<ArrayType> t,std::vector<std::shared_ptr<Value>> arr):Variable(n),ArrayValue(t,arr){
    
}

std::shared_ptr<Value> ArrayVariable::clone(){
    return std::make_shared<ArrayVariable>(name,type,clone_array());
}
