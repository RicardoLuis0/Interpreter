#ifndef INTERPRETER_EXPR_PART_VALUE_H
#define INTERPRETER_EXPR_PART_VALUE_H

#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartValue : public ExprPart {
        public:
            ExprPartValue(std::shared_ptr<Value>);
            ExprPartValue(std::string);
            static std::shared_ptr<ExprPartValue> from_int(int);
            static std::shared_ptr<ExprPartValue> from_double(double);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<DefaultFrame> context) override;
            std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context) override;
            std::shared_ptr<Value> value;
    };
}

#endif // INTERPRETER_EXPR_PART_VALUE_H
