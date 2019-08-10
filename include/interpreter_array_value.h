#ifndef INTERPRETER_ARRAY_VALUE_H
#define INTERPRETER_ARRAY_VALUE_H

#include "interpreter_value.h"
#include "interpreter_array_type.h"

namespace Interpreter {
    class ArrayValue : public virtual Value {
        public:
            ArrayValue(std::shared_ptr<ArrayType>);
            ArrayValue(std::shared_ptr<ArrayType>,std::vector<std::shared_ptr<Value>>);
            std::vector<std::shared_ptr<Value>> &get();
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> clone() override;
            virtual std::shared_ptr<Value> access_array(std::shared_ptr<Value>&) override;
        protected:
            std::vector<std::shared_ptr<Value>> clone_array();
            std::shared_ptr<ArrayType> type;
            std::vector<std::shared_ptr<Value>> array;
    };
}


#endif // INTERPRETER_ARRAY_VALUE_H
