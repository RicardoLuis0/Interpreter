#ifndef PARSER_VARIABLE_DEFINITION_MATCHER_H
#define PARSER_VARIABLE_DEFINITION_MATCHER_H


#include <memory>
#include "parser_component.h"
#include "parser_variable_definition.h"

namespace Parser{
    class VariableDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<VariableDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_VARIABLE_DEFINITION_MATCHER_H
