#ifndef INTERPRETER_ANY_TYPE_H
#define INTERPRETER_ANY_TYPE_H

#include "interpreter_type.h"

namespace Interpreter {
    class AnyType : public Type {
    public:
        bool is(std::shared_ptr<Type> self,std::shared_ptr<Type> other) override;
        std::string get_name() override;
    };
}

#endif // INTERPRETER_ANY_TYPE_H
