#ifndef PARSER_DEFINITION_MATCHER_H
#define PARSER_DEFINITION_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_definition.h"

namespace Parser{
    class DefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<Definition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_DEFINITION_MATCHER_H
