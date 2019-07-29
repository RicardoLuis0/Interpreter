#ifndef INTERPRETER_IF_STATEMENT_H
#define INTERPRETER_IF_STATEMENT_H

#include "interpreter_line.h"
#include "interpreter_default_frame.h"
#include "parser_if_statement.h"
#include "interpreter_expression.h"
#include "interpreter_code_block.h"

namespace Interpreter {
    class IfStatement : public Line {
        public:
            IfStatement(DefaultFrame * context,std::shared_ptr<Parser::IfStatement>);
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
            std::shared_ptr<Expression> condition;
            std::shared_ptr<CodeBlock> code;
            std::shared_ptr<CodeBlock> else_stmt;
    };
}

#endif // INTERPRETER_IF_STATEMENT_H
