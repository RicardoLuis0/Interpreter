#ifndef PARSER_VARIABLE_DEFINITION_H
#define PARSER_VARIABLE_DEFINITION_H

#include "parser_result_part.h"
#include "parser_expression.h"
#include "parser_var_type.h"
#include "parser_variable_definition_item.h"
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
