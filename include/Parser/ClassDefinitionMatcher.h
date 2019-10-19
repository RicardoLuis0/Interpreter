#ifndef PARSER_CLASS_DEFINITION_MATCHER_H
#define PARSER_CLASS_DEFINITION_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/ClassDefinition.h"

namespace Parser{
    class ClassDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<ClassDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_CLASS_DEFINITION_MATCHER_H
