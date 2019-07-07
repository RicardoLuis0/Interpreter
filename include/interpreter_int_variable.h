#ifndef INTERPRETER_INT_VARIABLE_H
#define INTERPRETER_INT_VARIABLE_H

#include "interpreter_int_value.h"
#include "interpreter_variable.h"

namespace Interpreter {
    class Int_Variable : public virtual Variable , public virtual Int_Value {
        public:
            Int_Variable(std::string,int);
    };
}

#endif // INTERPRETER_INT_VARIABLE_H
