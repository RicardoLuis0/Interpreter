#ifndef INTERPRETER_USER_FUNCTION_H
#define INTERPRETER_USER_FUNCTION_H

#include "interpreter_function.h"
#include "interpreter_default_frame.h"
#include "interpreter_exec_frame.h"
#include "interpreter_code_block.h"

namespace Interpreter {
    class UserFunction : public Function {
        public:
            UserFunction(DefaultFrame * parent,std::shared_ptr<Parser::FunctionDefinition>,bool delay=false);
            void proccess_delayed();
            std::string get_name() override;
            std::shared_ptr<Type> get_type() override;
            std::vector<FunctionParameter> get_parameters() override;
            std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override;
            //std::shared_ptr<ExecFrame> getFrame
        private:
            std::vector<FunctionParameter> build_parameters(DefaultFrame * context);
            std::shared_ptr<Parser::FunctionDefinition> function;
            std::vector<FunctionParameter> parameters;
            std::shared_ptr<DefaultFrame> frame;
            std::shared_ptr<CodeBlock> code;
            std::shared_ptr<Type> return_type;
            friend class CodeBlock;
    };
}

#endif // INTERPRETER_USER_FUNCTION_H
