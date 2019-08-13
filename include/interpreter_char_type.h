#ifndef INTERPRETER_CHAR_TYPE_H
#define INTERPRETER_CHAR_TYPE_H

#include "interpreter_primitive_type.h"

namespace Interpreter {
    class CharType : public PrimitiveType {
        public:
            std::string get_name() override;
    };
}

#endif // INTERPRETER_CHAR_TYPE_H
