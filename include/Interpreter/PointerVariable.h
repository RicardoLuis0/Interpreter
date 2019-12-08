#ifndef INTERPRETER_POINTER_VARIABLE_H
#define INTERPRETER_POINTER_VARIABLE_H

#include "Interpreter/Variable.h"
#include "Interpreter/PointerValue.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class PointerVariable : public virtual Variable , public virtual PointerValue {
        public:
            PointerVariable(std::string,std::shared_ptr<PointerType> type,std::shared_ptr<Value> value);
    };
}

#endif // INTERPRETER_POINTER_VARIABLE_H
