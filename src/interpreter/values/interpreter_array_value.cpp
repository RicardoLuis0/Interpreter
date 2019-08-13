#include "interpreter_array_value.h"
#include "interpreter_int_value.h"

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

std::shared_ptr<Value> ArrayValue::access_array(std::shared_ptr<Value> &v){
    return array.at(std::dynamic_pointer_cast<IntValue>(v)->get());
}

std::vector<std::shared_ptr<Value>> ArrayValue::clone_array(){
    std::vector<std::shared_ptr<Value>> c;
    for(std::shared_ptr<Value> val:array){
        c.push_back(val->clone());
    }
    return c;
}
