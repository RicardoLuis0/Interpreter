#ifndef INTERPRETER_POINTER_VARIABLE_H
#define INTERPRETER_POINTER_VARIABLE_H

#include "interpreter_variable.h"
#include "interpreter_pointer_value.h"

namespace Interpreter {
    class PointerVariable : public virtual Variable , public virtual PointerValue {
        public:
            PointerVariable(std::string,std::shared_ptr<class Type> type,std::shared_ptr<Value> value);
    };
}

#endif // INTERPRETER_POINTER_VARIABLE_H
