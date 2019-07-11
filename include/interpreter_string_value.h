#ifndef INTERPRETER_STRING_VALUE_H
#define INTERPRETER_STRING_VALUE_H

#include "interpreter_value.h"
#include "parser_var_type.h"

namespace Interpreter {
    class StringValue : public virtual Value {
        public:
            StringValue(std::string);
            operator std::string&();
            std::string &get();
            virtual std::shared_ptr<Parser::VarType> get_type() override;
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
