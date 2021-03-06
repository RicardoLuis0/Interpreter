#ifndef INTERPRETER_USER_FUNCTION_H
#define INTERPRETER_USER_FUNCTION_H

#include "Interpreter/Function.h"
#include "Interpreter/DefaultFrame.h"
#include "Interpreter/ExecFrame.h"
#include "Interpreter/CodeBlock.h"

namespace Interpreter {
    class UserFunction : public Function {
        public:
            UserFunction(DefaultFrame * parent,std::shared_ptr<Parser::FunctionDefinition>,bool delay=false);
            virtual void proccess_delayed();//should be safe to call multiple times
            std::string get_name() override;
            int get_line() override;
            std::shared_ptr<Type> get_type() override;
            std::vector<FunctionParameter> get_parameters() override;
            std::shared_ptr<Value> call(ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args) override;
            
            bool is_variadic() override;
            std::shared_ptr<Type> get_variadic_type() override;
            //std::shared_ptr<ExecFrame> getFrame
        protected:
            std::shared_ptr<Type> variadic_type;
            std::vector<FunctionParameter> build_parameters(DefaultFrame * context);
            std::shared_ptr<Parser::FunctionDefinition> function;
            std::vector<FunctionParameter> parameters;
            std::shared_ptr<Type> return_type;
            std::shared_ptr<DefaultFrame> frame;
            std::shared_ptr<CodeBlock> code;
            friend class CodeBlock;
            friend class DefaultFrame;
    };
}

#endif // INTERPRETER_USER_FUNCTION_H
