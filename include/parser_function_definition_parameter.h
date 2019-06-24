#ifndef PARSER_FUNCTION_DEFINITION_PARAMETER_H
#define PARSER_FUNCTION_DEFINITION_PARAMETER_H

#include "word_token.h"
#include "parser_result_part.h"
#include "parser_var_type.h"
#include <vector>

namespace Parser{
    class FunctionDefinitionParameter : public ParserResultPart {
        public:
            FunctionDefinitionParameter(std::shared_ptr<VarType>,std::shared_ptr<Lexer::WordToken>);
            FunctionDefinitionParameter(std::shared_ptr<VarType>,std::string);
            std::shared_ptr<VarType> type;
            std::string name;
        protected:
        private:
    };
}

#endif // PARSER_FUNCTION_DEFINITION_PARAMETER_H
