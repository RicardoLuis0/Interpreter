#ifndef INTERPRETER_FUNCTION_PARAMETER_H
#define INTERPRETER_FUNCTION_PARAMETER_H

#include "Parser/VarType.h"
#include "Parser/FunctionDefinitionParameter.h"
#include "Interpreter/Type.h"

namespace Interpreter {
    class FunctionParameter {
    public:
        FunctionParameter(std::shared_ptr<Type>);
        FunctionParameter(std::shared_ptr<Type>,std::string name,bool ref);
        static std::vector<FunctionParameter> from_pfdp(class DefaultFrame * context,std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>>);
        static std::string get_typelist(std::vector<FunctionParameter>,bool print_ref=false);
        bool operator==(const FunctionParameter &other)const;
        std::shared_ptr<Type> type;
        std::string name;
        bool is_reference;
    };
}

#endif // INTERPRETER_FUNCTION_PARAMETER_H
