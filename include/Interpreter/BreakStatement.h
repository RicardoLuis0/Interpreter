#ifndef INTERPRETER_BREAK_STATEMENT_H
#define INTERPRETER_BREAK_STATEMENT_H

#include "Interpreter/Line.h"
#include "Interpreter/ExecFrame.h"

namespace Interpreter {
    class BreakStatement : public Line {
        public:
            BreakStatement(int line);
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
    };
}

#endif // INTERPRETER_BREAK_STATEMENT_H
