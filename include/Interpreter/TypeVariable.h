#ifndef INTERPRETER_TYPE_VARIABLE_H
#define INTERPRETER_TYPE_VARIABLE_H

#include "Interpreter/TypeValue.h"
#include "Interpreter/Variable.h"

#ifdef _MSC_VER

//disable inheritance via dominance warning for MSVC

#pragma warning( disable : 4250 )

#endif

namespace Interpreter {
    class TypeVariable : public virtual Variable , public virtual TypeValue {
        public:
            TypeVariable(std::string,std::shared_ptr<Type>);
    };
}

#endif // INTERPRETER_TYPE_VARIABLE_H
