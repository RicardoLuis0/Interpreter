#ifndef PARSER_VARIABLE_DEFINITION_ITEM_MATCHER_H
#define PARSER_VARIABLE_DEFINITION_ITEM_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_variable_definition_item.h"

namespace Parser{
    class VariableDefinitionItemMatcher:BaseComponent{
        public:
            std::shared_ptr<VariableDefinitionItem> makeMatch(parserProgress&);
    };
}

#endif // PARSER_VARIABLE_DEFINITION_ITEM_MATCHER_H
