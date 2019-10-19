#ifndef PARSER_WHILE_STATEMENT_MATCHER_H
#define PARSER_WHILE_STATEMENT_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/WhileStatement.h"

namespace Parser{
    class WhileStatementMatcher:public BaseComponent{
    public:
        std::shared_ptr<WhileStatement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_WHILE_STATEMENT_MATCHER_H
