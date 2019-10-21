#ifndef INTERPRETER_FLOAT_VARIABLE_H
#define INTERPRETER_FLOAT_VARIABLE_H

#include "Interpreter/FloatValue.h"
#include "Interpreter/Variable.h"

namespace Interpreter {
    class FloatVariable : public virtual Variable , public virtual FloatValue {
        public:
            FloatVariable(std::string,double);
    };
}

#endif // INTERPRETER_FLOAT_VARIABLE_H
