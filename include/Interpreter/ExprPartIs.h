#ifndef INTERPRETER_EXPR_PART_IS_H
#define INTERPRETER_EXPR_PART_IS_H

#include "Interpreter/ExprPart.h"

namespace Interpreter {
    class ExprPartIs : public ExprPart {
        public:
            ExprPartIs(std::shared_ptr<ExprPart> type,std::shared_ptr<ExprPart> value);
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> eval(ExecFrame * context) override;
            std::shared_ptr<ExprPart> type_param;
            std::shared_ptr<ExprPart> param;
    };
}

#endif // INTERPRETER_EXPR_PART_IS_H
