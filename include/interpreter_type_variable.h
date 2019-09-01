#ifndef INTERPRETER_TYPE_VARIABLE_H
#define INTERPRETER_TYPE_VARIABLE_H

#include "interpreter_type_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class TypeVariable : public virtual Variable , public virtual TypeValue {
        public:
            TypeVariable(std::string,std::shared_ptr<Type>);
    };
}

#endif // INTERPRETER_TYPE_VARIABLE_H
