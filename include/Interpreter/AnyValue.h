#ifndef INTERPRETER_ANY_VALUE_H
#define INTERPRETER_ANY_VALUE_H

#include "Interpreter/Value.h"

namespace Interpreter {
    class AnyValue : public virtual Value {
    public:
        virtual std::shared_ptr<class Type> get_type() override;
        virtual std::shared_ptr<Value> clone() override;
        virtual std::shared_ptr<class Variable> clone_var(std::string new_name) override;
    };
}

#endif // INTERPRETER_ANY_VALUE_H
