#ifndef INTERPRETER_DUMMY_VARIABLE_H
#define INTERPRETER_DUMMY_VARIABLE_H

#include "Interpreter/DummyValue.h"
#include "Interpreter/Variable.h"

namespace Interpreter {
    class DummyVariable : public virtual Variable , public virtual DummyValue {
        public:
            DummyVariable(std::shared_ptr<Type>);
#ifdef _MSC_VER
            using DummyValue::*;
#endif
    };
}

#endif // INTERPRETER_DUMMY_VARIABLE_H
