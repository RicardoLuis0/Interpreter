#ifndef INTERPRETER_FLOAT_VARIABLE_H
#define INTERPRETER_FLOAT_VARIABLE_H

#include "interpreter_float_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class FloatVariable : public virtual Variable , public virtual FloatValue {
        public:
            FloatVariable(std::string,double);
    };
}

#endif // INTERPRETER_FLOAT_VARIABLE_H