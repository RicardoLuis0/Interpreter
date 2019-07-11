#ifndef INTERPRETER_EXPR_PART_OP_H
#define INTERPRETER_EXPR_PART_OP_H

#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartOp : public ExprPart {
        public:
            ExprPartOp(int);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<DefaultFrame> context) override;
            std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context) override;
            int op;
    };
}

#endif // INTERPRETER_EXPR_PART_OP_H
