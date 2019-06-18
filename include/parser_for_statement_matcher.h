#ifndef PARSER_FOR_STATEMENT_MATCHER_H
#define PARSER_FOR_STATEMENT_MATCHER_H

#include "parser_component.h"
#include "parser_for_statement.h"

namespace Parser{
    class ForStatementMatcher:BaseComponent{
    public:
        std::shared_ptr<ForStatement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_FOR_STATEMENT_MATCHER_H
