#ifndef PARSER_IF_STATMENT_MATCHER_H
#define PARSER_IF_STATMENT_MATCHER_H

#include "parser_component.h"
#include "parser_if_statement.h"

namespace Parser{
    class IfStatementMatcher:public BaseComponent{
    public:
        std::shared_ptr<IfStatement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_IF_STATMENT_MATCHER_H
