#ifndef PARSER_STRUCT_DEFINITION_MATCHER_H
#define PARSER_STRUCT_DEFINITION_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/StructDefinition.h"

namespace Parser{
    class StructDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<StructDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_STRUCT_DEFINITION_MATCHER_H
