#ifndef INTERPRETER_LINE_RESULT_SIMPLE_H
#define INTERPRETER_LINE_RESULT_SIMPLE_H

#include "Interpreter/LineResult.h"

namespace Interpreter {

    class LineResultSimple : public LineResult {
        public:
            LineResultSimple(LineResultAction_t action);
            virtual LineResultAction_t getAction() override;
        protected:
            LineResultAction_t action;
    };
}

#endif // INTERPRETER_LINE_RESULT_SIMPLE_H
