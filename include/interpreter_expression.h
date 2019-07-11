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
            Expression(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::Expression>);
            std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context);//parent_frame's defauls must be the same as the context the expression was built with
            std::shared_ptr<LineResult> run(std::shared_ptr<ExecFrame> context) override;
            std::shared_ptr<Parser::VarType> get_type();
        protected:
            static std::map<int,int> operator_precedence;
            std::stack<std::shared_ptr<ExprPart>> expression;
            std::shared_ptr<Parser::VarType> type;
            void add_term(std::shared_ptr<DefaultFrame>,std::shared_ptr<Parser::ExpressionTerm>);
            void add_expression(std::shared_ptr<DefaultFrame>,std::shared_ptr<Parser::Expression>);
            std::shared_ptr<Parser::VarType> get_type(std::shared_ptr<DefaultFrame> context,std::shared_ptr<ExprPart>);
            std::shared_ptr<Parser::VarType> check_op(std::shared_ptr<DefaultFrame> context,std::stack<std::shared_ptr<ExprPart>>&,std::shared_ptr<ExprPartOp>);
            std::shared_ptr<Parser::VarType> check(std::shared_ptr<DefaultFrame> context);//check for errors, validity
            std::shared_ptr<Value> eval_op(std::shared_ptr<ExecFrame> context,std::stack<std::shared_ptr<ExprPart>>&,std::shared_ptr<ExprPartOp>);
    };
}

#endif // INTERPRETER_EXPRESSION_H
