#ifndef INTERPRETER_UNSIGNED_CHAR_VARIABLE_H
#define INTERPRETER_UNSIGNED_CHAR_VARIABLE_H

#include "interpreter_unsigned_char_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class UnsignedCharVariable : public virtual Variable , public virtual UnsignedCharValue {
        public:
            UnsignedCharVariable(std::string,unsigned char);
    };
}

#endif // INTERPRETER_UNSIGNED_CHAR_VARIABLE_H
