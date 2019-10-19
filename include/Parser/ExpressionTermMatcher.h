#ifndef PARSER_EXPRESSION_TERM_MATCHER_H
#define PARSER_EXPRESSION_TERM_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/ExpressionTerm.h"

namespace Parser{
    class ExpressionTermMatcher:BaseComponent{
        public:
            std::shared_ptr<ExpressionTerm> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_TERM_MATCHER_H
