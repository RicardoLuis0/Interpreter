#ifndef INTERPRETER_STRING_VARIABLE_H
#define INTERPRETER_STRING_VARIABLE_H

#include "interpreter_string_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class StringVariable : public virtual Variable , public virtual StringValue {
        public:
            StringVariable(std::string,std::string);
            virtual std::shared_ptr<Value> clone() override;
    };
}

#endif // INTERPRETER_STRING_VARIABLE_H
