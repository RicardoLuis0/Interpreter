#ifndef PARSER_IF_STATMENT_MATCHER_H
#define PARSER_IF_STATMENT_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/IfStatement.h"

namespace Parser{
    class IfStatementMatcher:public BaseComponent{
    public:
        std::shared_ptr<IfStatement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_IF_STATMENT_MATCHER_H
