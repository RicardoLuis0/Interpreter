#ifndef INTERPRETER_RUNTIME_ERROR_H
#define INTERPRETER_RUNTIME_ERROR_H

#include <string>
#include <stdexcept>

namespace MyExcept {
    class InterpreterRuntimeError : public std::runtime_error {
            public:
                explicit InterpreterRuntimeError(const std::string& error);
                explicit InterpreterRuntimeError(const int &line,const std::string& error);
                explicit InterpreterRuntimeError(const int &line,const std::string& error,const std::string &filename);
    };
};

#endif // INTERPRETER_RUNTIME_ERROR_H
