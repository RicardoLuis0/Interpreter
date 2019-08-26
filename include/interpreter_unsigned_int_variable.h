#ifndef INTERPRETER_UNSIGNED_INT_VARIABLE_H
#define INTERPRETER_UNSIGNED_INT_VARIABLE_H

#include "interpreter_unsigned_int_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class UnsignedIntVariable : public virtual Variable , public virtual UnsignedIntValue {
        public:
            UnsignedIntVariable(std::string,unsigned int);
    };
}

#endif // INTERPRETER_UNSIGNED_INT_VARIABLE_H
