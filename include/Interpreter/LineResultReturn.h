#ifndef INTERPRETER_LINE_RESULT_RETURN_H
#define INTERPRETER_LINE_RESULT_RETURN_H

#include "Interpreter/LineResultSimple.h"
#include "Interpreter/Expression.h"

namespace Interpreter {

    class LineResultReturn : public LineResultSimple {
        public:
            LineResultReturn(std::shared_ptr<Value> value,int line);
            std::shared_ptr<Value> get();
            int get_line();
        protected:
            std::shared_ptr<Value> value;
            int line;
    };
}

#endif // INTERPRETER_LINE_RESULT_RETURN_H
