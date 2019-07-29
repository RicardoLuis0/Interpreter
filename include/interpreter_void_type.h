#ifndef INTERPRETER_VOID_TYPE_H
#define INTERPRETER_VOID_TYPE_H

#include "interpreter_type.h"

namespace Interpreter {
    class VoidType : public Type {
        std::shared_ptr<Value> get_operator_result(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) override;
        std::shared_ptr<Value> call_operator(int op,std::shared_ptr<Value> self,std::shared_ptr<Value> other) override;
        std::shared_ptr<Value> make_value() override;
        std::shared_ptr<Variable> make_variable(std::string name) override;
    };
}

#endif // INTERPRETER_VOID_TYPE_H
