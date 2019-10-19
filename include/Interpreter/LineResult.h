#ifndef INTERPRETER_LINE_RESULT_H
#define INTERPRETER_LINE_RESULT_H

namespace Interpreter {
    enum LineResultAction_t {
        ACTION_NONE,
        ACTION_BREAK,
        ACTION_CONTINUE,
        ACTION_RETURN,
    };
    class LineResult {
        public:
            virtual LineResultAction_t getAction()=0;
    };
}

#endif // INTERPRETER_LINE_RESULT_H
