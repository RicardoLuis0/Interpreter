#ifndef PARSER_STATEMENT_MATCHER_H
#define PARSER_STATEMENT_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_statement.h"

namespace Parser{
    class StatementMatcher:BaseComponent{
        public:
            std::shared_ptr<Statement> makeMatch(parserProgress&);
    };
}

#endif // PARSER_STATEMENT_MATCHER_H
