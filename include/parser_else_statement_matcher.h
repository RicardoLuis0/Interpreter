#ifndef PARSER_ELSE_STATEMENT_MATCHER_H
#define PARSER_ELSE_STATEMENT_MATCHER_H

#include "parser_component.h"
#include "parser_else_statement.h"

namespace Parser{
    class ElseStatementMatcher:public BaseComponent{
    public:
        std::shared_ptr<ElseStatement> makeMatch(parserProgress&);
    };
}


#endif // PARSER_ELSE_STATEMENT_MATCHER_H
