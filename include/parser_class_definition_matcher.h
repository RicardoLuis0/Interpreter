#ifndef PARSER_CLASS_DEFINITION_MATCHER_H
#define PARSER_CLASS_DEFINITION_MATCHER_H

//TODO

#include <memory>
#include "parser_component.h"
#include "parser_class_definition.h"

namespace Parser{
    class ClassDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<ClassDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_CLASS_DEFINITION_MATCHER_H
