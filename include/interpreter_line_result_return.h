#ifndef INTERPRETER_LINE_RESULT_RETURN_H
#define INTERPRETER_LINE_RESULT_RETURN_H

#include "interpreter_line_result_simple.h"
#include "interpreter_expression.h"

namespace Interpreter {

    class LineResultReturn : public LineResultSimple {
        public:
            LineResultReturn(std::shared_ptr<Value> value);
            std::shared_ptr<Value> get();
        protected:
            std::shared_ptr<Value> value;
    };
}

#endif // INTERPRETER_LINE_RESULT_RETURN_H
