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
    if CHECK2(UnsignedIntValue,v1) {
        return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME OPERATOR v1->get()));
    }else if CHECK2(UnsignedCharValue,v2) {
        return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME OPERATOR v2->get()));
    }else if CHECK2(IntValue,v3) {
        return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME OPERATOR (static_cast<unsigned int>(v3->get()))));
    }else if CHECK2(CharValue,v4) {
        return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME OPERATOR (static_cast<unsigned char>(v4->get()))));
    #else
    if CHECK2(IntValue,v1) {
        return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME OPERATOR v1->get()));
    }else if CHECK2(CharValue,v2) {
        return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME OPERATOR v2->get()));
    #endif
    }else if CHECK2(FloatValue,v5) {
        return std::make_shared<IntValue>(static_cast<int>(VALUE_NAME OPERATOR v5->get()));
    }else{
        throw std::runtime_error("invalid types for operator '" OPERATOR_STRING "'");
    }
}

#undef OPERATOR_STRING
#undef OPERATOR
#undef METHOD_NAME
