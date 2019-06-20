#ifndef PARSER_RETURN_STATEMENT_MATCHER_H
#define PARSER_RETURN_STATEMENT_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_return_statement.h"

namespace Parser{
    class ReturnStatementMatcher:BaseComponent{
        public:
            std::shared_ptr<ReturnStatement> makeMatch(parserProgress&);
    };
}


#endif // PARSER_RETURN_STATEMENT_MATCHER_H
