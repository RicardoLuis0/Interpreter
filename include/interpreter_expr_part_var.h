#ifndef INTERPRETER_EXPR_PART_VAR_H
#define INTERPRETER_EXPR_PART_VAR_H

#include "interpreter_expr_part.h"

namespace Interpreter {
    class ExprPartVar : public ExprPart {
        public:
            ExprPartVar(std::shared_ptr<DefaultFrame> context,std::string);
            std::shared_ptr<Parser::VarType> get_type() override;
            std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context) override;
            std::shared_ptr<Parser::VarType> type;
            std::string ident;
    };
}

#endif // INTERPRETER_EXPR_PART_VAR_H
