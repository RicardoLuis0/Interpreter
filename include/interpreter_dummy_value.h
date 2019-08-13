#ifndef INTERPRETER_DUMMY_VALUE_H
#define INTERPRETER_DUMMY_VALUE_H

#include "interpreter_value.h"

namespace Interpreter {
    class DummyValue : public virtual Value {
            std::shared_ptr<Type> t;
        public:
            DummyValue(std::shared_ptr<Type>);
            std::shared_ptr<class Type> get_type() override;
            virtual std::shared_ptr<Value> clone() override;
            virtual std::shared_ptr<class Variable> clone_var(std::string new_name) override;
            
    };
}
#endif // INTERPRETER_DUMMY_VALUE_H
