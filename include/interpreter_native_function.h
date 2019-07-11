#ifndef INTERPRETER_NATIVE_FUNCTION_H
#define INTERPRETER_NATIVE_FUNCTION_H

//NOTE native functions to make later
//printf(string format,mixed ... args)
//puts(string)
//putc(int)
//stoi(string)
//stof(string)
//to_string(mixed<int,float>)

#include "interpreter_function.h"
#include "interpreter_exec_frame.h"

namespace Interpreter {
    class NativeFunction : public Function {//base class
        public:
    };
}

#endif // INTERPRETER_NATIVE_FUNCTION_H