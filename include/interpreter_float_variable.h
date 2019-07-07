#ifndef INTERPRETER_FLOAT_VARIABLE_H
#define INTERPRETER_FLOAT_VARIABLE_H

#include "interpreter_float_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class Float_Variable : public virtual Variable , public virtual Float_Value {
        public:
            Float_Variable(std::string,double);
    };
}

#endif // INTERPRETER_FLOAT_VARIABLE_H
