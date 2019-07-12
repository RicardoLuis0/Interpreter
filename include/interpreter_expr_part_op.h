#ifndef INTERPRETER_EXPR_PART_OP_H
#define INTERPRETER_EXPR_PART_OP_H

#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartOp : public ExprPart {
        public:
            ExprPartOp(std::shared_ptr<ExprPart> left,int op,std::shared_ptr<ExprPart> right);
            std::shared_ptr<Parser::VarType> get_type() override;
            std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context) override;
            std::shared_ptr<ExprPart> left;
            std::shared_ptr<ExprPart> right;
            int op;
            std::shared_ptr<Parser::VarType> type;
    };
}

#endif // INTERPRETER_EXPR_PART_OP_H
