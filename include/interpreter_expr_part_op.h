#ifndef INTERPRETER_EXPR_PART_OP_H
#define INTERPRETER_EXPR_PART_OP_H

#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartOp : public ExprPart {
        public:
            ExprPartOp(std::shared_ptr<ExprPart> left,int op,std::shared_ptr<ExprPart> right,int line_start,int line_end);
            std::shared_ptr<Value> get_dummy_type() override;
            std::shared_ptr<Type> get_type() override;
            std::shared_ptr<Value> eval(ExecFrame * context) override;
            std::shared_ptr<ExprPart> left;
            std::shared_ptr<ExprPart> right;
            int op;
            //std::shared_ptr<Type> type;
            std::shared_ptr<Value> dummyType;
    };
}

#endif // INTERPRETER_EXPR_PART_OP_H
