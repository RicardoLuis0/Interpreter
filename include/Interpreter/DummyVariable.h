#ifndef INTERPRETER_DUMMY_VARIABLE_H
#define INTERPRETER_DUMMY_VARIABLE_H

#include "Interpreter/DummyValue.h"
#include "Interpreter/Variable.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class DummyVariable : public virtual Variable , public virtual DummyValue {
        public:
            DummyVariable(std::shared_ptr<Type>);
    };
}

#endif // INTERPRETER_DUMMY_VARIABLE_H
