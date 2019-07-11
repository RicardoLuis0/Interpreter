#ifndef INTERPRETER_WHILE_STATEMENT_H
#define INTERPRETER_WHILE_STATEMENT_H

#include "interpreter_line.h"
#include "parser_while_statement.h"
#include "interpreter_expression.h"
#include "interpreter_code_block.h"

namespace Interpreter {
    class WhileStatement : public Line {
        public:
            WhileStatement(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::WhileStatement>);
            std::shared_ptr<LineResult> run(std::shared_ptr<ExecFrame> context) override;
            std::shared_ptr<Expression> condition;
            std::shared_ptr<CodeBlock> code;
    };
}

#endif // INTERPRETER_WHILE_STATEMENT_H
