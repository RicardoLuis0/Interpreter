#ifndef INTERPRETER_EXEC_FRAME_H
#define INTERPRETER_EXEC_FRAME_H

#include <map>
#include <memory>
#include "interpreter_default_frame.h"

namespace Interpreter {
    class ExecFrame{
        public:
            ExecFrame(ExecFrame * parent,DefaultFrame * defaults);
            ExecFrame * parent;
            DefaultFrame * defaults;
            std::map<std::string,std::shared_ptr<Variable>> variables;
            std::shared_ptr<Variable> get_variable(std::string);
            std::shared_ptr<Function> get_function(std::string);
            void set_args(std::map<std::string,std::shared_ptr<Value>>);
            std::shared_ptr<Value> fn_call(std::shared_ptr<Function>,std::vector<std::shared_ptr<Value>>);
    };
}

#endif // INTERPRETER_EXEC_FRAME_H
