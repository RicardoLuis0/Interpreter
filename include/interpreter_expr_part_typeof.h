#ifndef INTERPRETER_EXPR_PART_TYPEOF_H
#define INTERPRETER_EXPR_PART_TYPEOF_H


#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartTypeOf : public ExprPart {
        public:
            ExprPartTypeOf(std::shared_ptr<ExprPart> value);
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> eval(ExecFrame * context) override;
            std::shared_ptr<ExprPart> param;
    };
}

#endif // INTERPRETER_EXPR_PART_TYPEOF_H
