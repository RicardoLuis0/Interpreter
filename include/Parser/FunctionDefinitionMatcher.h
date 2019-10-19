#ifndef PARSER_FUNCTION_DEFINITION_MATCHER_H
#define PARSER_FUNCTION_DEFINITION_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/FunctionDefinition.h"

namespace Parser{
    class FunctionDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<FunctionDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_FUNCTION_DEFINITION_MATCHER_H
