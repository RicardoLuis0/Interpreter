#ifndef INTERPRETER_EXPR_PART_INIT_VLA_H
#define INTERPRETER_EXPR_PART_INIT_VLA_H

#include "Interpreter/ExprPart.h"
#include "Interpreter/ArrayType.h"

namespace Interpreter {
    class ExprPartInitVLA : public ExprPart {
        public:
            ExprPartInitVLA(std::shared_ptr<ArrayType> arr_type,std::string name);
            virtual std::shared_ptr<Type> get_type() override;
            virtual std::shared_ptr<Value> eval(ExecFrame * context) override;
            std::shared_ptr<ArrayType> arr_type;
            std::string name;
    };
}
#endif // INTERPRETER_EXPR_PART_INIT_VLA_H
