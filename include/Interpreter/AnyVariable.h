#ifndef INTERPRETER_ANY_VARIABLE_H
#define INTERPRETER_ANY_VARIABLE_H

#include "Interpreter/Variable.h"
#include "Interpreter/AnyValue.h"

namespace Interpreter {
    class AnyVariable : public virtual Variable , public virtual AnyValue {
        public:
            AnyVariable(std::string);
#ifdef _MSC_VER
            using AnyValue::*;
#endif
    };
}

#endif // INTERPRETER_ANY_VARIABLE_H
