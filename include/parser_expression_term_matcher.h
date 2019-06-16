#ifndef PARSER_EXPRESSION_TERM_MATCHER_H
#define PARSER_EXPRESSION_TERM_MATCHER_H

#include "parser_component.h"
#include "parser_expression_term.h"

namespace Parser{
    class ExpressionTermMatcher:BaseComponent{
        public:
            std::shared_ptr<ExpressionTerm> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_TERM_MATCHER_H
