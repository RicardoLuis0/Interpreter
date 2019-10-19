#include "Interpreter/ArrayValue.h"
#include "Interpreter/ArrayVariable.h"
#include "Interpreter/IntValue.h"
#include "Util/InterpreterUtilDefinesMisc.h"

#include "Interpreter/CharValue.h"
#include "Interpreter/UnsignedCharValue.h"
#include "Interpreter/IntValue.h"
#include "Interpreter/UnsignedIntValue.h"
#include "Interpreter/FloatValue.h"
#include "Interpreter/StringValue.h"

#include "Interpreter/valueToString.h"

using namespace Interpreter;

ArrayValue::ArrayValue(std::shared_ptr<ArrayType> t):type(t){
    int size=type->get_size();
    if(size>0){
        std::shared_ptr<Type> t2=type->get_type();
        for(int i=0;i<size;i++){
            array.push_back(t2->make_value(t2));
        }
    }
}

ArrayValue::ArrayValue(std::shared_ptr<ArrayValue> val):type(val->type),array(val->clone_array()){
}

const std::string & ArrayValue::getString(){
    if(array.empty()){
        temp="{}";
        return temp;
    }
    temp="{ ";
    bool first=true;
    for(std::shared_ptr<Value> val:array){
        if(!first){
            temp+=", ";
        }
        temp+=valueToString(val);
        if(first)first=false;
    }
    temp+=" }";
    return temp;
}

ArrayValue::ArrayValue(std::shared_ptr<ArrayType> t,std::vector<std::shared_ptr<Value>> arr):type(t),array(arr){
}

std::vector<std::shared_ptr<Value>> & ArrayValue::get(){
    return array;
}

std::shared_ptr<Type> ArrayValue::get_type(){
    return type;
}

std::shared_ptr<Value> ArrayValue::clone(){
    return std::make_shared<ArrayValue>(type,clone_array());
}

std::shared_ptr<Variable> ArrayValue::clone_var(std::string new_name){
    return std::make_shared<ArrayVariable>(new_name,type,clone_array());
}

std::shared_ptr<Value> ArrayValue::access_array(std::shared_ptr<Value> &v){
    if(!CHECKPTR(v,IntValue))throw std::runtime_error("invalid types for operator '[]'");
    return array.at(std::dynamic_pointer_cast<IntValue>(v)->get());
}

std::vector<std::shared_ptr<Value>> ArrayValue::clone_array(){
    std::vector<std::shared_ptr<Value>> c;
    for(std::shared_ptr<Value> val:array){
        c.push_back(val->clone());
    }
    return c;
}
