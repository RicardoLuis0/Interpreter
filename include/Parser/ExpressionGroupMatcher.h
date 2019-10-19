#ifndef PARSER_EXPRESSION_GROUP_MATCHER_H
#define PARSER_EXPRESSION_GROUP_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/ExpressionGroup.h"

namespace Parser{
    class ExpressionGroupMatcher:BaseComponent{
        public:
            std::shared_ptr<ExpressionGroup> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_GROUP_MATCHER_H
