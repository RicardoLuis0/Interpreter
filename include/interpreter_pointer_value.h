#ifndef INTERPRETER_POINTER_VALUE_H
#define INTERPRETER_POINTER_VALUE_H

#include "interpreter_value.h"

namespace Interpreter {
    class PointerValue : public virtual Value {
    public:
        PointerValue(std::shared_ptr<class Type> type,std::shared_ptr<Value> value);
        virtual std::shared_ptr<class Type> get_type() override;
        virtual std::shared_ptr<Value>& get_value();
        virtual std::shared_ptr<Value> clone() override;
        virtual std::shared_ptr<class Variable> clone_var(std::string new_name) override;
    private:
        std::shared_ptr<class Type> type;
        std::shared_ptr<Value> value;
    };
}

#endif // INTERPRETER_POINTER_VALUE_H
