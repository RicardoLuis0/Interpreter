#ifndef INTERPRETER_CHAR_VARIABLE_H
#define INTERPRETER_CHAR_VARIABLE_H

#include "Interpreter/CharValue.h"
#include "Interpreter/Variable.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class CharVariable : public virtual Variable , public virtual CharValue {
        public:
            CharVariable(std::string,char);
    };
}

#endif // INTERPRETER_CHAR_VARIABLE_H
