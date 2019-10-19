#ifndef PARSER_EXPRESSION_MATCHER_H
#define PARSER_EXPRESSION_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/Expression.h"

namespace Parser{
    class ExpressionMatcher:BaseComponent{
        public:
            std::shared_ptr<Expression> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_MATCHER_H
