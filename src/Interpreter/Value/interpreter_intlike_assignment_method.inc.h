#ifndef METHOD_NAME
#error Missing METHOD_NAME
#endif

#ifndef OPERATOR
#error Missing OPERATOR
#endif

#ifndef OPERATOR_STRING
#error Missing OPERATOR_STRING
#endif

std::shared_ptr<Value> CLASS_NAME::METHOD_NAME(std::shared_ptr<Value> &other){
    #ifdef UNSIGNED
    if CHECK2(UnsignedIntValue,v4) {
        VALUE_NAME OPERATOR v4->get();
    }else if CHECK2(UnsignedCharValue,v5) {
        VALUE_NAME OPERATOR v5->get();
    }else
    #endif
    if CHECK2(IntValue,v1) {
        VALUE_NAME OPERATOR v1->get();
    }else if CHECK2(CharValue,v2) {
        VALUE_NAME OPERATOR v2->get();
    }else if CHECK2(FloatValue,v3) {
        VALUE_NAME OPERATOR v3->get();
    }else{
        throw std::runtime_error("invalid types for operator '" OPERATOR_STRING "'");
    }
    return nullptr;
}

#undef OPERATOR_STRING
#undef OPERATOR
#undef METHOD_NAME
