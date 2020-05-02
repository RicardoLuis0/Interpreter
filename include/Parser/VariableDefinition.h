#ifndef PARSER_VARIABLE_DEFINITION_H
#define PARSER_VARIABLE_DEFINITION_H

#include "Parser/ParserResultPart.h"
#include "Parser/Expression.h"
#include "Parser/VarType.h"
#include "Parser/VariableDefinitionItem.h"
#include <vector>

namespace Parser{
    class VariableDefinition : public ParserResultPart {
    public:
        VariableDefinition(parserProgress&);
        VariableDefinition(int line_start,std::shared_ptr<VarType> type,int line_start_2,std::shared_ptr<Lexer::WordToken> ident,parserProgress&);//partial constructor
        VariableDefinition(std::shared_ptr<VarType> type,std::vector<std::shared_ptr<VariableDefinitionItem>> variables,int line_start,int line_end);
        std::shared_ptr<VarType> type;
        std::vector<std::shared_ptr<VariableDefinitionItem>> variables;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_VARIABLE_DEFINITION_H
