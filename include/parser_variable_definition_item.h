#ifndef PARSER_VARIABLE_DEFINITION_ITEM_H
#define PARSER_VARIABLE_DEFINITION_ITEM_H

#include "word_token.h"
#include "parser_result_part.h"
#include "parser_expression.h"

namespace Parser{
    class VariableDefinitionItem : public ParserResultPart {
        public:
            VariableDefinitionItem(std::shared_ptr<Lexer::WordToken>,std::shared_ptr<Expression>);
            std::string name;
            std::shared_ptr<Expression> value;
        protected:
        private:
    };
}

#endif // PARSER_VARIABLE_DEFINITION_ITEM_H
