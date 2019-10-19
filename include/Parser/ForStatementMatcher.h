#ifndef PARSER_FOR_STATEMENT_MATCHER_H
#define PARSER_FOR_STATEMENT_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/ForStatement.h"

namespace Parser{
    class ForStatementMatcher:BaseComponent{
    public:
        std::shared_ptr<ForStatement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_FOR_STATEMENT_MATCHER_H
