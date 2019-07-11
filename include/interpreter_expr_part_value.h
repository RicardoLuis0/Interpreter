#ifndef INTERPRETER_EXPR_PART_VALUE_H
#define INTERPRETER_EXPR_PART_VALUE_H

#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartValue : public ExprPart {
        public:
            ExprPartValue(int);
            ExprPartValue(double);
            ExprPartValue(std::string);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<DefaultFrame> context) override;
            std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context) override;
            std::shared_ptr<Value> value;
    };
}

#endif // INTERPRETER_EXPR_PART_VALUE_H
