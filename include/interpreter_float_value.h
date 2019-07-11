#ifndef INTERPRETER_FLOAT_VALUE_H
#define INTERPRETER_FLOAT_VALUE_H

#include "interpreter_value.h"
#include "parser_var_type.h"

namespace Interpreter {
    class FloatValue : public virtual Value {
        protected:
            double value;
        public:
            FloatValue(double);
            operator double&();
            double &get();
            virtual std::shared_ptr<Parser::VarType> get_type() override;
    };
}

#endif // INTERPRETER_FLOAT_VALUE_H
