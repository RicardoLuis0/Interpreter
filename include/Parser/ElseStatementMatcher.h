#ifndef PARSER_ELSE_STATEMENT_MATCHER_H
#define PARSER_ELSE_STATEMENT_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/ElseStatement.h"

namespace Parser{
    class ElseStatementMatcher:public BaseComponent{
    public:
        std::shared_ptr<ElseStatement> makeMatch(parserProgress&);
    };
}


#endif // PARSER_ELSE_STATEMENT_MATCHER_H
