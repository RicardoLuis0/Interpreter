#ifndef PARSER_MEMBER_DEFINITION_MATCHER_H
#define PARSER_MEMBER_DEFINITION_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_member_definition.h"

namespace Parser{
    class MemberDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<MemberDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_MEMBER_DEFINITION_MATCHER_H
