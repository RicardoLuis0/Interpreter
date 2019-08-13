#ifndef INTERPRETER_UNSIGNED_INT_TYPE_H
#define INTERPRETER_UNSIGNED_INT_TYPE_H

#include "interpreter_primitive_type.h"

namespace Interpreter {
    class UnsignedIntType : public PrimitiveType {
        public:
            std::string get_name() override;
    };
}

#endif // INTERPRETER_UNSIGNED_INT_TYPE_H
