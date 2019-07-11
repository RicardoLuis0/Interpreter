#ifndef INTERPRETER_FOR_STATEMENT_H
#define INTERPRETER_FOR_STATEMENT_H

#include "interpreter_line.h"
#include "parser_for_statement.h"
#include "interpreter_expression.h"
#include "interpreter_code_block.h"

namespace Interpreter {
    class ForStatement : public Line {
        public:
            ForStatement(std::shared_ptr<DefaultFrame> context,std::shared_ptr<Parser::ForStatement>);
            std::shared_ptr<LineResult> run(std::shared_ptr<ExecFrame> context) override;
            std::shared_ptr<Expression> pre;
            std::shared_ptr<Expression> condition;
            std::shared_ptr<Expression> inc;
            std::shared_ptr<CodeBlock> code;
    };
}

#endif // INTERPRETER_FOR_STATEMENT_H
