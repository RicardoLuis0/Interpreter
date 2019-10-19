#ifndef PARSER_VARIABLE_DEFINITION_H
#define PARSER_VARIABLE_DEFINITION_H

#include "Parser/ResultPart.h"
#include "Parser/Expression.h"
#include "Parser/VarType.h"
#include "Parser/VariableDefinitionItem.h"
#include <vector>

namespace Parser{
    class VariableDefinition : public ParserResultPart {
        public:
            VariableDefinition(std::shared_ptr<VarType> type,std::vector<std::shared_ptr<VariableDefinitionItem>> variables,int line_start,int line_end);
            std::shared_ptr<VarType> type;
            std::vector<std::shared_ptr<VariableDefinitionItem>> variables;
    };
}

#endif // PARSER_VARIABLE_DEFINITION_H
