#ifndef INTERPRETER_LINE_H
#define INTERPRETER_LINE_H

#include <memory>
#include "interpreter_line_result.h"
#include "interpreter_exec_frame.h"

namespace Interpreter {
    class Line {
        public:
            virtual std::shared_ptr<LineResult> run(ExecFrame * context)=0;
    };
}

#endif // INTERPRETER_LINE_H
