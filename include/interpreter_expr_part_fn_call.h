#ifndef INTERPRETER_EXPR_PART_FN_CALL_H
#define INTERPRETER_EXPR_PART_FN_CALL_H

#include "interpreter_expr_part.h"
#include "parser_function_call.h"
#include "interpreter_expression.h"

namespace Interpreter {
    class ExprPartFnCall : public ExprPart {
        public:
            ExprPartFnCall(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::FunctionCall>);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<DefaultFrame> context) override;
            std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context) override;
        protected:
            std::string ident;
            std::vector<std::shared_ptr<Expression>> arguments;
    };
}

#endif // INTERPRETER_EXPR_PART_FN_CALL_H