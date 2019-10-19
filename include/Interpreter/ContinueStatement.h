#ifndef INTERPRETER_CONTINUE_STATEMENT_H
#define INTERPRETER_CONTINUE_STATEMENT_H

#include "Interpreter/Line.h"
#include "Interpreter/ExecFrame.h"

namespace Interpreter {
    class ContinueStatement : public Line {
        public:
            ContinueStatement(int line);
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
    };
}

#endif // INTERPRETER_CONTINUE_STATEMENT_H
