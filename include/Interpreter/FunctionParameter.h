#ifndef INTERPRETER_FUNCTION_PARAMETER_H
#define INTERPRETER_FUNCTION_PARAMETER_H

#include "Parser/VarType.h"
#include "Parser/FunctionDefinitionParameter.h"
#include "Interpreter/Type.h"

namespace Interpreter {
    class FunctionParameter {
    public:
        FunctionParameter(std::shared_ptr<Type>);
        FunctionParameter(std::shared_ptr<Type>,std::string name);
        static std::vector<FunctionParameter> from_pfdp(class DefaultFrame * context,std::vector<std::shared_ptr<Parser::FunctionDefinitionParameter>>);
        static std::string get_typelist(std::vector<FunctionParameter>);
        bool operator==(const FunctionParameter &other)const;
        std::shared_ptr<Type> type;
        std::string name;
    };
}

#endif // INTERPRETER_FUNCTION_PARAMETER_H
