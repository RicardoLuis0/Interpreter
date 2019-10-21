#ifndef INTERPRETER_CHAR_VARIABLE_H
#define INTERPRETER_CHAR_VARIABLE_H

#include "Interpreter/CharValue.h"
#include "Interpreter/Variable.h"

namespace Interpreter {
    class CharVariable : public virtual Variable , public virtual CharValue {
        public:
            CharVariable(std::string,char);
#ifdef _MSC_VER
            using CharValue::*;
#endif
    };
}

#endif // INTERPRETER_CHAR_VARIABLE_H
