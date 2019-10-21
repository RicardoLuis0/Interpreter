#ifndef INTERPRETER_UNSIGNED_CHAR_VARIABLE_H
#define INTERPRETER_UNSIGNED_CHAR_VARIABLE_H

#include "Interpreter/UnsignedCharValue.h"
#include "Interpreter/Variable.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class UnsignedCharVariable : public virtual Variable , public virtual UnsignedCharValue {
        public:
            UnsignedCharVariable(std::string,unsigned char);
    };
}

#endif // INTERPRETER_UNSIGNED_CHAR_VARIABLE_H
