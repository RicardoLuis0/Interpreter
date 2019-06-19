#ifndef PARSER_FUNCTION_DEFINITION_MATCHER_H
#define PARSER_FUNCTION_DEFINITION_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_function_definition.h"

namespace Parser{
    class FunctionDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<FunctionDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_FUNCTION_DEFINITION_MATCHER_H
