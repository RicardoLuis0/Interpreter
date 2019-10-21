#ifndef INTERPRETER_TYPE_VARIABLE_H
#define INTERPRETER_TYPE_VARIABLE_H

#include "Interpreter/TypeValue.h"
#include "Interpreter/Variable.h"

namespace Interpreter {
    class TypeVariable : public virtual Variable , public virtual TypeValue {
        public:
            TypeVariable(std::string,std::shared_ptr<Type>);
#ifdef _MSC_VER
            using TypeValue::*;
#endif
    };
}

#endif // INTERPRETER_TYPE_VARIABLE_H
