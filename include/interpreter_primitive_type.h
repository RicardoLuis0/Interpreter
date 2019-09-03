#ifndef INTERPRETER_PRIMITIVE_TYPE_H
#define INTERPRETER_PRIMITIVE_TYPE_H

#include "interpreter_type.h"

namespace Interpreter {
    class PrimitiveType : public Type {
        public:
            PrimitiveType(bool is_const=false);
    };
}

#endif // INTERPRETER_PRIMITIVE_TYPE_H
