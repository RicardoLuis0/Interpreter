#ifndef INTERPRETER_USER_FUNCTION_H
#define INTERPRETER_USER_FUNCTION_H

#include "interpreter_function.h"
#include "interpreter_default_frame.h"

namespace Interpreter {
    class UserFunction : public Function {
        public:
            UserFunction(DefaultFrame * parent,std::shared_ptr<Parser::FunctionDefinition>);
            std::string get_name() override;
            std::shared_ptr<Parser::VarType> get_type() override;
            std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters() override;
            //std::shared_ptr<Value> call(std::shared_ptr<ExecFrame>,std::map<std::string,std::shared_ptr<Value>> args) override;
        private:
            friend class CodeBlock;
            std::shared_ptr<Parser::FunctionDefinition> function;
            std::shared_ptr<DefaultFrame> frame;
    };
}

#endif // INTERPRETER_USER_FUNCTION_H
