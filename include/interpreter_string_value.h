#ifndef INTERPRETER_STRING_VALUE_H
#define INTERPRETER_STRING_VALUE_H

#include "interpreter_value.h"
#include "interpreter_type.h"
#include "printf_value_container.h"

namespace Interpreter {
    class StringValue : public virtual Value , public Printf::StringContainer {
        public:
            virtual const std::string & getString() override;
            
            StringValue(std::string);
            operator std::string&();
            std::string &get();
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> clone() override;
            virtual std::shared_ptr<class Variable> clone_var(std::string new_name) override;
            
            //operators
            virtual std::shared_ptr<Value> eq(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> neq(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> assign_add(std::shared_ptr<Value>&) override;
            virtual std::shared_ptr<Value> add(std::shared_ptr<Value>&) override;
        protected:
            std::string value;
    };
}

#endif // INTERPRETER_STRING_VALUE_H
