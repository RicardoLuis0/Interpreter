#ifndef PARSER_VARIABLE_DEFINITION_H
#define PARSER_VARIABLE_DEFINITION_H

#include "word_token.h"
#include "parser_result_part.h"
#include "parser_expression.h"

namespace Parser{
    class VariableDefinition : public ParserResultPart {
        public:
            VariableDefinition(std::shared_ptr<Lexer::WordToken>,std::shared_ptr<Expression>);
            std::shared_ptr<Lexer::WordToken> name;
            std::shared_ptr<Expression> value;
        protected:
        private:
    };
}

#endif // PARSER_VARIABLE_DEFINITION_H
