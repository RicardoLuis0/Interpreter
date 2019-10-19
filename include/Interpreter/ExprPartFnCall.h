#ifndef INTERPRETER_EXPR_PART_FN_CALL_H
#define INTERPRETER_EXPR_PART_FN_CALL_H

#include "Interpreter/ExprPart.h"
#include "Parser/FunctionCall.h"
#include "Interpreter/Expression.h"

namespace Interpreter {
    class ExprPartFnCall : public ExprPart {
        public:
            ExprPartFnCall(DefaultFrame * context,std::shared_ptr<Parser::FunctionCall>);
            std::shared_ptr<Type> get_type() override;
            std::shared_ptr<Value> eval(ExecFrame * context) override;
        protected:
            std::string ident;
            std::vector<FunctionParameter> param_types;
            std::vector<std::shared_ptr<Expression>> arguments;
            std::shared_ptr<Type> type;
    };
}

#endif // INTERPRETER_EXPR_PART_FN_CALL_H
