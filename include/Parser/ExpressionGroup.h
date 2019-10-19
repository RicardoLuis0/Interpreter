#ifndef PARSER_EXPRESSION_GROUP_H
#define PARSER_EXPRESSION_GROUP_H

#include <memory>
#include "Parser/Expression.h"

namespace Parser{
    class ExpressionGroup:public ParserResultPart {
        public:
            ExpressionGroup(std::shared_ptr<Expression>,int line_start,int line_end);
            std::shared_ptr<Expression> contents;
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_GROUP_H
