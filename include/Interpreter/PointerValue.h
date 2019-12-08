#ifndef INTERPRETER_POINTER_VALUE_H
#define INTERPRETER_POINTER_VALUE_H

#include "Interpreter/Value.h"
#include "Interpreter/Variable.h"
#include "Interpreter/valueToString.h"
#include "Printf/ValueContainer.h"
#include "Interpreter/PointerType.h"

namespace Interpreter {
    class PointerValue : public virtual Value , public virtual Printf::StringContainer {
    public:
        virtual const std::string & getString() override;
        PointerValue(std::shared_ptr<PointerType> type,std::shared_ptr<Value> value);
        virtual std::shared_ptr<Type> get_type() override;
        virtual std::shared_ptr<Value>& get_value();
        virtual std::shared_ptr<Value> clone() override;
        virtual std::shared_ptr<Variable> clone_var(std::string new_name) override;
    private:
        std::shared_ptr<PointerType> type;
        std::shared_ptr<Value> value;
        std::string temp;
    };
}

#endif // INTERPRETER_POINTER_VALUE_H
