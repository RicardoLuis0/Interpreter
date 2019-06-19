#ifndef PARSER_FUNCTION_DEFINITION_H
#define PARSER_FUNCTION_DEFINITION_H

#include "word_token.h"
#include "parser_result_part.h"
#include "parser_function_definition_parameter.h"
#include <vector>

namespace Parser{
    class FunctionDefinition : public ParserResultPart {
        public:
            FunctionDefinition(std::shared_ptr<Lexer::WordToken>,std::vector<std::shared_ptr<FunctionDefinitionParameter>>);
            std::shared_ptr<Lexer::WordToken> name;
            std::vector<std::shared_ptr<FunctionDefinitionParameter>> parameters;
        protected:
        private:
    };
}

#endif // PARSER_FUNCTION_DEFINITION_H
