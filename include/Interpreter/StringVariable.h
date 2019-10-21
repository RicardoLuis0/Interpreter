#ifndef INTERPRETER_STRING_VARIABLE_H
#define INTERPRETER_STRING_VARIABLE_H

#include "Interpreter/StringValue.h"
#include "Interpreter/Variable.h"

namespace Interpreter {
    class StringVariable : public virtual Variable , public virtual StringValue {
        public:
            StringVariable(std::string,std::string);
#ifdef _MSC_VER
            using StringValue::*;
#endif
    };
}

#endif // INTERPRETER_STRING_VARIABLE_H
