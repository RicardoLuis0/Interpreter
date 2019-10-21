#ifndef INTERPRETER_INT_VARIABLE_H
#define INTERPRETER_INT_VARIABLE_H

#include "Interpreter/IntValue.h"
#include "Interpreter/Variable.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class IntVariable : public virtual Variable , public virtual IntValue {
        public:
            IntVariable(std::string,int);
    };
}

#endif // INTERPRETER_INT_VARIABLE_H
