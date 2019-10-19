#ifndef INTERPRETER_EXEC_FRAME_H
#define INTERPRETER_EXEC_FRAME_H

#include <map>
#include <memory>
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/Variable.h"
#include "Interpreter/Function.h"

namespace Interpreter {
    class ExecFrame{
        protected:
            void set_variable(std::string,std::shared_ptr<Value>,std::shared_ptr<Type>,bool reference=false);
            std::map<std::string,std::shared_ptr<Variable>> variables;
            ExecFrame * parent;
            class DefaultFrame * defaults;
            friend class ForStatement;
            friend class UserFunction;
            friend class ExprPartInitVLA;
        public:
            ExecFrame(ExecFrame * parent,class DefaultFrame * defaults);
            std::shared_ptr<Variable> get_variable(std::string);
            std::shared_ptr<Function> get_function(std::string,std::vector<FunctionParameter>);
            void set_args(std::map<std::string,std::pair<std::shared_ptr<Value>,std::pair<bool,std::shared_ptr<Type>>>>);
            std::shared_ptr<Value> fn_call(std::shared_ptr<Function>,std::vector<std::shared_ptr<Value>>);
    };
}

#endif // INTERPRETER_EXEC_FRAME_H
