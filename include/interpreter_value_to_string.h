#ifndef INTERPRETER_VALUE_TO_STRING_H_INCLUDED
#define INTERPRETER_VALUE_TO_STRING_H_INCLUDED

#include <memory>
#include <string>
#include "interpreter_value.h"
namespace Interpreter {
    std::string valueToString(std::shared_ptr<Value> val);
}
#endif // INTERPRETER_VALUE_TO_STRING_H_INCLUDED
