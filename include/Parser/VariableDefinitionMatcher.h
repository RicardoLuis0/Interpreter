#ifndef PARSER_VARIABLE_DEFINITION_MATCHER_H
#define PARSER_VARIABLE_DEFINITION_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/VariableDefinition.h"

namespace Parser{
    class VariableDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<VariableDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_VARIABLE_DEFINITION_MATCHER_H
