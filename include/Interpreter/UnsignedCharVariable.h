#ifndef INTERPRETER_UNSIGNED_CHAR_VARIABLE_H
#define INTERPRETER_UNSIGNED_CHAR_VARIABLE_H

#include "Interpreter/UnsignedCharValue.h"
#include "Interpreter/Variable.h"

namespace Interpreter {
    class UnsignedCharVariable : public virtual Variable , public virtual UnsignedCharValue {
        public:
            UnsignedCharVariable(std::string,unsigned char);
    };
}

#endif // INTERPRETER_UNSIGNED_CHAR_VARIABLE_H
