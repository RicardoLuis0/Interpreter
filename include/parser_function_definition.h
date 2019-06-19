#ifndef PARSER_FUNCTION_DEFINITION_H
#define PARSER_FUNCTION_DEFINITION_H

#include "parser_result_part.h"
#include "word_token.h"
#include <vector>

namespace Parser{
    class FunctionDefinition : public ParserResultPart {
        public:
            FunctionDefinition(std::shared_ptr<Lexer::WordToken>,std::vector<std::shared_ptr<FunctionDefinitionParameter>>);
        protected:
        private:
    };
}

#endif // PARSER_FUNCTION_DEFINITION_H
