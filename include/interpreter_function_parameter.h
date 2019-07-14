#ifndef INTERPRETER_FUNCTION_PARAMETER_H
#define INTERPRETER_FUNCTION_PARAMETER_H

#include "parser_var_type.h"
#include "parser_function_definition_parameter.h"

namespace Interpreter {
    class FunctionParameter {
    public:
        FunctionParameter(std::shared_ptr<Parser::VarType>);
        FunctionParameter(std::shared_ptr<Parser::VarType>,std::string name,bool ref);
        static std::vector<FunctionParameter> from_pfdp(std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>>);
        static std::string get_typelist(std::vector<FunctionParameter>,bool print_ref=false);
        bool operator==(const FunctionParameter &other)const;
        std::shared_ptr<Parser::VarType> type;
        std::string name;
        bool is_reference;
    };
}

#endif // INTERPRETER_FUNCTION_PARAMETER_H
