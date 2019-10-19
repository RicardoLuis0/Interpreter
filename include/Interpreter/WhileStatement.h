#ifndef INTERPRETER_WHILE_STATEMENT_H
#define INTERPRETER_WHILE_STATEMENT_H

#include "Interpreter/Line.h"
#include "Parser/WhileStatement.h"
#include "Interpreter/Expression.h"
#include "Interpreter/CodeBlock.h"

namespace Interpreter {
    class WhileStatement : public Line {
        public:
            WhileStatement(DefaultFrame * context,std::shared_ptr<Parser::WhileStatement>);
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
            std::shared_ptr<Expression> condition;
            std::shared_ptr<CodeBlock> code;
    };
}

#endif // INTERPRETER_WHILE_STATEMENT_H
