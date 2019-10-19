#ifndef PARSER_DEFINITION_MATCHER_H
#define PARSER_DEFINITION_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/Definition.h"

namespace Parser{
    class DefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<Definition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_DEFINITION_MATCHER_H
