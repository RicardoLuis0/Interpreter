#ifndef INTERPRETER_BOOL_TYPE_H
#define INTERPRETER_BOOL_TYPE_H

#include "interpreter_primitive_type.h"

namespace Interpreter {
    class BoolType : public PrimitiveType {
        public:
            std::string get_name() override;
    };
}

#endif // INTERPRETER_BOOL_TYPE_H
