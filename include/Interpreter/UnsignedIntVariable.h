#ifndef INTERPRETER_UNSIGNED_INT_VARIABLE_H
#define INTERPRETER_UNSIGNED_INT_VARIABLE_H

#include "Interpreter/UnsignedIntValue.h"
#include "Interpreter/Variable.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class UnsignedIntVariable : public virtual Variable , public virtual UnsignedIntValue {
        public:
            UnsignedIntVariable(std::string,unsigned int);
    };
}

#endif // INTERPRETER_UNSIGNED_INT_VARIABLE_H
