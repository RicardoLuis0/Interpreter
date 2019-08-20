#ifndef INTERPRETER_PRIMITIVE_VALUE_H
#define INTERPRETER_PRIMITIVE_VALUE_H

#include "interpreter_value.h"

namespace Interpreter {
    class PrimitiveValue : public virtual Value {
        protected:
        union {
            int ivalue;
            double dvalue;
            char cvalue;
            unsigned int uivalue;
            unsigned char ucvalue;
        };
    };
}

#endif // INTERPRETER_PRIMITIVE_VALUE_H
