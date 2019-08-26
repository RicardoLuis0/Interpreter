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
        return std::make_shared<UnsignedIntValue>( VALUE_NAME OPERATOR val->get());
    }else if CHECK(UnsignedCharValue) {
        #if CLASS_NAME == UnsignedCharValue
        return std::make_shared<UnsignedCharValue>( VALUE_NAME OPERATOR val->get());
        #else
        return std::make_shared<UnsignedIntValue>( VALUE_NAME OPERATOR val->get());
        #endif
    }else
    #endif
    if CHECK(IntValue) {
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR val->get());
    }else if CHECK(CharValue) {
        #if CLASS_NAME == CharValue
        return std::make_shared<CharValue>( VALUE_NAME OPERATOR val->get());
        #else
        return std::make_shared<IntValue>( VALUE_NAME OPERATOR val->get());
        #endif
    }else{
        throw std::runtime_error("invalid types for operator '" OPERATOR_STRING "'");
    }
}

#undef OPERATOR_STRING
#undef OPERATOR
#undef METHOD_NAME
