#ifndef INTERPRETER_LINE_H
#define INTERPRETER_LINE_H

#include <memory>
#include "Interpreter/LineResult.h"
#include "Interpreter/ExecFrame.h"

namespace Interpreter {
    class Line {
        public:
            Line(int source_line);
            virtual ~Line()=default;
            virtual std::shared_ptr<LineResult> run(ExecFrame * context)=0;
            int get_source_line();
        protected:
            int source_line;
    };
}

#endif // INTERPRETER_LINE_H
