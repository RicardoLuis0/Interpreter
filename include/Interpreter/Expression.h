#ifndef INTERPRETER_EXPRESSION_H
#define INTERPRETER_EXPRESSION_H

#include <stack>

#include "Interpreter/DefaultFrame.h"
#include "Interpreter/ExprPart.h"
#include "Interpreter/ExprPartOp.h"
#include "Interpreter/Line.h"

#include "Parser/ExpressionTerm.h"

namespace Interpreter {
    class Expression : public Line {
        public:
            static std::shared_ptr<Expression> expr_assign_ignore_const(DefaultFrame * context,std::string varname,std::shared_ptr<Parser::Expression> assign_val,int line);
            Expression(DefaultFrame * context,std::shared_ptr<Parser::Expression>);
            Expression(std::shared_ptr<ExprPart>,int line);
            std::shared_ptr<Value> eval(ExecFrame * context);//parent_frame's defauls must be the same as the context the expression was built with
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
            std::shared_ptr<Type> get_type();
            std::shared_ptr<Value> get_dummy_type();
        protected:
            std::shared_ptr<ExprPart> expression;
            static std::shared_ptr<ExprPart> get_term(DefaultFrame *,std::shared_ptr<Parser::ExpressionTerm>);
            static std::shared_ptr<ExprPart> get_expression(DefaultFrame *,std::shared_ptr<Parser::Expression>);
    };
}

#endif // INTERPRETER_EXPRESSION_H
