#ifndef PARSER_VARIABLE_DEFINITION_ITEM_H
#define PARSER_VARIABLE_DEFINITION_ITEM_H

#include "Lexer/WordToken.h"
#include "Parser/ResultPart.h"
#include "Parser/Expression.h"

namespace Parser{
    class VariableDefinitionItem : public ParserResultPart {
        public:
            VariableDefinitionItem(std::string,int line_start,int line_end);
            VariableDefinitionItem(std::shared_ptr<Lexer::WordToken>,std::shared_ptr<Expression>,int line_start,int line_end);
            std::string name;
            std::shared_ptr<Expression> value;
        protected:
        private:
    };
}

#endif // PARSER_VARIABLE_DEFINITION_ITEM_H
