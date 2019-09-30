#ifndef INTERPRETER_TYPE_VALUE_H
#define INTERPRETER_TYPE_VALUE_H

#include "interpreter_value.h"
#include "interpreter_type.h"
#include "printf_value_container.h"

namespace Interpreter {
    class TypeValue : public virtual Value , public virtual Printf::StringContainer{
        public:
            virtual const std::string & getString() override;
            
            TypeValue(std::shared_ptr<Type>);
            std::shared_ptr<Type> &get();
            
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> clone() override;
            virtual std::shared_ptr<class Variable> clone_var(std::string new_name) override;
            
            //operators
            virtual std::shared_ptr<Value> eq(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> neq(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign(std::shared_ptr<Value>&) override;
        protected:
            std::shared_ptr<Type> value;
            std::string temp;
    };
}

#endif // INTERPRETER_TYPE_VALUE_H
