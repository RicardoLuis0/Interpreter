#ifndef INTERPRETER_EXEC_FRAME_H
#define INTERPRETER_EXEC_FRAME_H

#include <unordered_map>
#include <memory>
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/Variable.h"
#include "Interpreter/Function.h"

namespace Interpreter {
    class ExecFrame{
        public:
            void set_variable(std::string,std::shared_ptr<Value>,std::shared_ptr<Type>);
            std::unordered_map<std::string,std::shared_ptr<Variable>> variables;
            ExecFrame * parent;
            class DefaultFrame * defaults;
            ExecFrame(ExecFrame * parent,class DefaultFrame * defaults);
            std::shared_ptr<Variable> get_variable(std::string);
            std::shared_ptr<Function> get_function(std::string,std::vector<FunctionParameter>);
            void set_args(std::unordered_map<std::string,std::pair<std::shared_ptr<Value>,std::shared_ptr<Type>>>);
            std::shared_ptr<Value> fn_call(std::shared_ptr<Function>,std::vector<std::shared_ptr<Value>>);
    };
}

#endif // INTERPRETER_EXEC_FRAME_H
