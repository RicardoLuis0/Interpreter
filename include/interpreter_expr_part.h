#ifndef INTERPRETER_EXPR_PART_H
#define INTERPRETER_EXPR_PART_H

#include <memory>
#include "interpreter_default_frame.h"
#include "interpreter_exec_frame.h"
#include "interpreter_value.h"

namespace Interpreter {
    class ExprPart {
        public:
            virtual std::shared_ptr<Type> get_type()=0;
            virtual std::shared_ptr<Value> eval(std::shared_ptr<ExecFrame> context)=0;
    };
}

#endif // INTERPRETER_EXPR_PART_H
