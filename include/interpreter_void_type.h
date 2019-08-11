#ifndef INTERPRETER_VOID_TYPE_H
#define INTERPRETER_VOID_TYPE_H

#include "interpreter_type.h"

namespace Interpreter {
    class VoidType : public Type {
    public:
        std::string get_name() override;
    };
}

#endif // INTERPRETER_VOID_TYPE_H
