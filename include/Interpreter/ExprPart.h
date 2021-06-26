#ifndef INTERPRETER_EXPR_PART_H
#define INTERPRETER_EXPR_PART_H

#include <memory>
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/ExecFrame.h"
#include "Interpreter/Value.h"

namespace Interpreter {
    class ExprPart {
        public:
            virtual ~ExprPart()=default;
            virtual std::shared_ptr<Type> get_type()=0;
            virtual std::shared_ptr<Value> get_dummy_type();
            virtual std::shared_ptr<Value> eval(ExecFrame * context)=0;
    };
}

#endif // INTERPRETER_EXPR_PART_H
