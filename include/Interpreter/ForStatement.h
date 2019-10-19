#ifndef INTERPRETER_FOR_STATEMENT_H
#define INTERPRETER_FOR_STATEMENT_H

#include "Interpreter/Line.h"
#include "Parser/ForStatement.h"
#include "Interpreter/Expression.h"
#include "Interpreter/CodeBlock.h"

namespace Interpreter {
    class ForStatement : public Line {
        public:
            ForStatement(DefaultFrame * context,std::shared_ptr<Parser::ForStatement>);
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
            std::shared_ptr<Expression> pre;
            std::shared_ptr<Expression> condition;
            std::shared_ptr<Expression> inc;
            std::shared_ptr<DefaultFrame> defFrame;
            std::shared_ptr<CodeBlock> code;
    };
}

#endif // INTERPRETER_FOR_STATEMENT_H
