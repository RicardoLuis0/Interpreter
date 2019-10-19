#include "Interpreter/ArrayVariable.h"

using namespace Interpreter;

ArrayVariable::ArrayVariable(std::string n,std::shared_ptr<ArrayType> t):Variable(n),ArrayValue(t){
    
}

ArrayVariable::ArrayVariable(std::string n,std::shared_ptr<ArrayValue> v):Variable(n),ArrayValue(v){
    
}

ArrayVariable::ArrayVariable(std::string n,std::shared_ptr<ArrayType> t,std::vector<std::shared_ptr<Value>> arr):Variable(n),ArrayValue(t,arr){
    
}
