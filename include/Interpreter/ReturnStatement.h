#ifndef INTERPRETER_RETURN_STATEMENT_H
#define INTERPRETER_RETURN_STATEMENT_H

#include "Interpreter/Line.h"
#include "Interpreter/DefaultFrame.h"
#include "Parser/ReturnStatement.h"
#include "Interpreter/ExecFrame.h"
#include "Interpreter/Expression.h"

namespace Interpreter {
    class ReturnStatement : public Line {
        public:
            ReturnStatement(DefaultFrame * context,std::shared_ptr<Parser::ReturnStatement>);
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
            std::shared_ptr<Expression> value;
            int line;
    };
}

#endif // INTERPRETER_RETURN_STATEMENT_H
