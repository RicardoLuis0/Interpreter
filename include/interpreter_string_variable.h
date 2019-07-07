#ifndef INTERPRETER_STRING_VARIABLE_H
#define INTERPRETER_STRING_VARIABLE_H

#include "interpreter_string_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class String_Variable : public virtual Variable , public virtual String_Value {
        public:
            String_Variable(std::string,std::string);
    };
}

#endif // INTERPRETER_STRING_VARIABLE_H
