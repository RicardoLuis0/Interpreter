#ifndef INTERPRETER_IF_STATEMENT_H
#define INTERPRETER_IF_STATEMENT_H

#include "Interpreter/Line.h"
#include "Interpreter/DefaultFrame.h"
#include "Parser/IfStatement.h"
#include "Interpreter/Expression.h"
#include "Interpreter/CodeBlock.h"

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
