#ifndef INTERPRETER_VALUE_TO_STRING_H_INCLUDED
#define INTERPRETER_VALUE_TO_STRING_H_INCLUDED

#include <memory>
#include <string>
#include "Interpreter/Value.h"
namespace Interpreter {
    std::string valueToString(std::shared_ptr<Value> val);//implementation in deflib.cpp
}
#endif // INTERPRETER_VALUE_TO_STRING_H_INCLUDED
