#ifndef PARSER_WHILE_STATEMENT_MATCHER_H
#define PARSER_WHILE_STATEMENT_MATCHER_H

#include "parser_component.h"
#include "parser_while_statement.h"

namespace Parser{
    class WhileStatementMatcher:public BaseComponent{
    public:
        std::shared_ptr<WhileStatement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_WHILE_STATEMENT_MATCHER_H
