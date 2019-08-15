#ifndef INTERPRETER_BREAK_STATEMENT_H
#define INTERPRETER_BREAK_STATEMENT_H

#include "interpreter_line.h"
#include "interpreter_exec_frame.h"

namespace Interpreter {
    class BreakStatement : public Line {
        public:
            std::shared_ptr<LineResult> run(ExecFrame * context) override;
    };
}

#endif // INTERPRETER_BREAK_STATEMENT_H
