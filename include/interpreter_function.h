#ifndef INTERPRETER_FUNCTION_H
#define INTERPRETER_FUNCTION_H

#include "parser_var_type.h"
#include "interpreter_value.h"
#include "parser_function_definition_parameter.h"
#include "interpreter_line_result.h"
#include "interpreter_function_parameter.h"

namespace Interpreter {
    class Function {
        public:
            virtual std::string get_name()=0;
            virtual std::shared_ptr<Type> get_type()=0;
            virtual std::vector<FunctionParameter> get_parameters()=0;
            virtual std::shared_ptr<Value> call(class ExecFrame * parent_frame,std::vector<std::shared_ptr<Value>> args)=0;
    };
}

#endif // INTERPRETER_FUNCTION_H
