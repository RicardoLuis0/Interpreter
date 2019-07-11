#ifndef INTERPRETER_FUNCTION_H
#define INTERPRETER_FUNCTION_H

#include "parser_var_type.h"
#include "interpreter_value.h"
//#include "interpreter_exec_frame.h"
#include "parser_function_definition_parameter.h"

namespace Interpreter {
    class Function {
        public:
            virtual std::string get_name()=0;
            virtual std::shared_ptr<Parser::VarType> get_type()=0;
            virtual std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>> get_parameters()=0;
            //virtual std::shared_ptr<Value> call(std::shared_ptr<ExecFrame> parent_frame,std::vector<std::shared_ptr<Value>> args)=0;
    };
}

#endif // INTERPRETER_FUNCTION_H
