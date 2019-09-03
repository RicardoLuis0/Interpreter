#ifndef INTERPRETER_EXPRESSION_H
#define INTERPRETER_EXPRESSION_H

#include <stack>

#include "interpreter_default_frame.h"
#include "interpreter_expr_part.h"
#include "interpreter_expr_part_op.h"
#include "interpreter_line.h"

#include "parser_expression_term.h"

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
