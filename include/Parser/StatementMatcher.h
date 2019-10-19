#ifndef PARSER_STATEMENT_MATCHER_H
#define PARSER_STATEMENT_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/Statement.h"

namespace Parser{
    class StatementMatcher:BaseComponent{
        public:
            std::shared_ptr<Statement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_STATEMENT_MATCHER_H
