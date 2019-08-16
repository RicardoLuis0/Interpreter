#ifndef INTERPRETER_RETURN_STATEMENT_H
#define INTERPRETER_RETURN_STATEMENT_H

#include "interpreter_line.h"
#include "interpreter_default_frame.h"
#include "parser_return_statement.h"
#include "interpreter_exec_frame.h"
#include "interpreter_expression.h"

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
