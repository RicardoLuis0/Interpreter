#ifndef INTERPRETER_ARRAY_VALUE_H
#define INTERPRETER_ARRAY_VALUE_H

#include "Interpreter/Value.h"
#include "Interpreter/ArrayType.h"
#include "Printf/ValueContainer.h"

namespace Interpreter {
    class ArrayValue : public virtual Value , public virtual Printf::StringContainer {
        public:
            ArrayValue(std::shared_ptr<ArrayType>);
            ArrayValue(std::shared_ptr<ArrayValue>);
            ArrayValue(std::shared_ptr<ArrayType>,std::vector<std::shared_ptr<Value>>);
            virtual const std::string & getString() override;
            std::vector<std::shared_ptr<Value>> &get();
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> clone() override;
            virtual std::shared_ptr<class Variable> clone_var(std::string new_name) override;
            virtual std::shared_ptr<Value> access_array(std::shared_ptr<Value>&) override;
        protected:
            std::vector<std::shared_ptr<Value>> clone_array();
            std::shared_ptr<ArrayType> type;
            std::vector<std::shared_ptr<Value>> array;
            std::string temp;
            friend class ArrayType;
    };
}


#endif // INTERPRETER_ARRAY_VALUE_H
