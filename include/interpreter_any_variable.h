#ifndef INTERPRETER_ANY_VARIABLE_H
#define INTERPRETER_ANY_VARIABLE_H

#include "interpreter_variable.h"
#include "interpreter_any_value.h"

namespace Interpreter {
    class AnyVariable : public virtual Variable , public virtual AnyValue {
        public:
            AnyVariable(std::string);
    };
}

#endif // INTERPRETER_ANY_VARIABLE_H
