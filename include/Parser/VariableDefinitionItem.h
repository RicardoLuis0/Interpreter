#ifndef PARSER_VARIABLE_DEFINITION_ITEM_H
#define PARSER_VARIABLE_DEFINITION_ITEM_H

#include "Lexer/WordToken.h"
#include "Parser/ParserResultPart.h"
#include "Parser/Expression.h"

namespace Parser{
    class VariableDefinitionItem : public ParserResultPart {
    public:
        VariableDefinitionItem(parserProgress&);
        VariableDefinitionItem(std::string,int line_start,int line_end);
        VariableDefinitionItem(std::shared_ptr<Lexer::WordToken>,std::shared_ptr<Expression>,int line_start,int line_end);
        std::string name;
        std::shared_ptr<Expression> value;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    protected:
    private:
    };
}

#endif // PARSER_VARIABLE_DEFINITION_ITEM_H
