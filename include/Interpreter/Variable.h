#ifndef INTERPRETER_VARIABLE_H
#define INTERPRETER_VARIABLE_H

#include "Interpreter/Value.h"

namespace Interpreter {
    class Variable : public virtual Value {
        public:
            virtual std::string get_name();
        protected:
            Variable(std::string);
            std::string name;
    };
}

#endif // INTERPRETER_VARIABLE_H
