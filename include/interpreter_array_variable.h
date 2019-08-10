#ifndef INTERPRETER_ARRAY_VARIABLE_H
#define INTERPRETER_ARRAY_VARIABLE_H

#include "interpreter_array_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class ArrayVariable : public virtual Variable , public virtual ArrayValue {
        public:
            ArrayVariable(std::string,std::shared_ptr<ArrayType>);
            ArrayVariable(std::string,std::shared_ptr<ArrayType>,std::vector<std::shared_ptr<Value>>);
            virtual std::shared_ptr<Value> clone() override;
    };
}

#endif // INTERPRETER_ARRAY_VARIABLE_H
