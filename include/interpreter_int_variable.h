#ifndef INTERPRETER_INT_VARIABLE_H
#define INTERPRETER_INT_VARIABLE_H

#include "interpreter_int_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class IntVariable : public virtual Variable , public virtual IntValue {
        public:
            IntVariable(std::string,int);
            virtual std::shared_ptr<Value> clone() override;
    };
}

#endif // INTERPRETER_INT_VARIABLE_H
