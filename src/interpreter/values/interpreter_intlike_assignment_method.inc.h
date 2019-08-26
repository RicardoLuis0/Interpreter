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
    if CHECK(UnsignedIntValue) {
        VALUE_NAME OPERATOR val->get();
    }else if CHECK(UnsignedCharValue) {
        VALUE_NAME OPERATOR val->get();
    }else
    #endif
    if CHECK(IntValue) {
        VALUE_NAME OPERATOR val->get();
    }else if CHECK(CharValue) {
        VALUE_NAME OPERATOR val->get();
    }else if CHECK(FloatValue) {
        VALUE_NAME OPERATOR val->get();
    }else{
        throw std::runtime_error("invalid types for operator '" OPERATOR_STRING "'");
    }
    return nullptr;
}

#undef OPERATOR_STRING
#undef OPERATOR
#undef METHOD_NAME
