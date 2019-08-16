#ifndef INTERPRETER_EXPR_PART_UNARY_OP_H
#define INTERPRETER_EXPR_PART_UNARY_OP_H

#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartUnaryOp : public ExprPart {
        public:
            ExprPartUnaryOp(std::shared_ptr<ExprPart> val,int op,bool pre,int line_start,int line_end);
            std::shared_ptr<Value> get_dummy_type() override;
            std::shared_ptr<Type> get_type() override;
            std::shared_ptr<Value> eval(ExecFrame * context) override;
            std::shared_ptr<ExprPart> val;
            int op;
            bool pre;
            std::shared_ptr<Value> dummyType;
    };
}

#endif // INTERPRETER_EXPR_PART_UNARY_OP_H
