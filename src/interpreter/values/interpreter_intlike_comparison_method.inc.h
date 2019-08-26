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
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR val->get());
    }else if CHECK(UnsignedCharValue) {
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR val->get());
    }else if CHECK(IntValue) {
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR ((unsigned int)val->get()));
    }else if CHECK(CharValue) {
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR ((unsigned char)val->get()));
    #else
    if CHECK(IntValue) {
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR val->get());
    }else if CHECK(CharValue) {
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR val->get());
    #endif
    }else if CHECK(FloatValue) {
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR val->get());
    }else{
        throw std::runtime_error("invalid types for operator '" OPERATOR_STRING "'");
    }
}

#undef OPERATOR_STRING
#undef OPERATOR
#undef METHOD_NAME
