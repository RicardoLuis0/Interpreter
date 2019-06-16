#ifndef PARSER_EXPRESSION_MATCHER_H
#define PARSER_EXPRESSION_MATCHER_H

#include "parser_component.h"
#include "parser_expression.h"

namespace Parser{
    class ExpressionMatcher:BaseComponent{
        public:
            std::shared_ptr<Expression> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_MATCHER_H
