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
        VariableDefinition(std::shared_ptr<VarType> type,std::vector<std::shared_ptr<VariableDefinitionItem>> variables,int line_start,int line_end);
        std::shared_ptr<VarType> type;
        std::vector<std::shared_ptr<VariableDefinitionItem>> variables;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_VARIABLE_DEFINITION_H
