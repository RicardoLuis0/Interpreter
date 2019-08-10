#ifndef INTERPRETER_DUMMY_VARIABLE_H
#define INTERPRETER_DUMMY_VARIABLE_H

#include "interpreter_dummy_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class DummyVariable : public virtual Variable , public virtual DummyValue {
        public:
            DummyVariable(std::shared_ptr<Type>);
            virtual std::shared_ptr<Value> clone() override;
    };
}

#endif // INTERPRETER_DUMMY_VARIABLE_H
