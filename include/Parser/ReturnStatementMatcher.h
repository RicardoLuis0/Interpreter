#ifndef PARSER_RETURN_STATEMENT_MATCHER_H
#define PARSER_RETURN_STATEMENT_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/ReturnStatement.h"

namespace Parser{
    class ReturnStatementMatcher:BaseComponent{
        public:
            std::shared_ptr<ReturnStatement> makeMatch(parserProgress&);
    };
}


#endif // PARSER_RETURN_STATEMENT_MATCHER_H
