#ifndef PARSER_MEMBER_DEFINITION_MATCHER_H
#define PARSER_MEMBER_DEFINITION_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/MemberDefinition.h"

namespace Parser{
    class MemberDefinitionMatcher:BaseComponent{
        public:
            std::shared_ptr<MemberDefinition> makeMatch(parserProgress&);
    };
}

#endif // PARSER_MEMBER_DEFINITION_MATCHER_H
