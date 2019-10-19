#ifndef PARSER_EXPRESSION_LIST_MATCHER_H
#define PARSER_EXPRESSION_LIST_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/ExpressionList.h"

namespace Parser{
    class ExpressionListMatcher:public BaseComponent{
    public:
        std::shared_ptr<ExpressionList> makeMatch(parserProgress&);
    };
}

#endif // PARSER_EXPRESSION_LIST_MATCHER_H
