#ifndef INTERPRETER_ANY_VARIABLE_H
#define INTERPRETER_ANY_VARIABLE_H

#include "Interpreter/Variable.h"
#include "Interpreter/AnyValue.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class AnyVariable : public virtual Variable , public virtual AnyValue {
        public:
            AnyVariable(std::string);
    };
}

#endif // INTERPRETER_ANY_VARIABLE_H
