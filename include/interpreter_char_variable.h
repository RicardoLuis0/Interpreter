#ifndef INTERPRETER_CHAR_VARIABLE_H
#define INTERPRETER_CHAR_VARIABLE_H

#include "interpreter_char_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class CharVariable : public virtual Variable , public virtual CharValue {
        public:
            CharVariable(std::string,char);
    };
}

#endif // INTERPRETER_CHAR_VARIABLE_H
