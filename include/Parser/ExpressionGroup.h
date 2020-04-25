#ifndef PARSER_EXPRESSION_GROUP_H
#define PARSER_EXPRESSION_GROUP_H

#include <memory>
#include "Parser/Expression.h"

namespace Parser{
    class ExpressionGroup:public ParserResultPart {
        public:
            ExpressionGroup(parserProgress&);
            ExpressionGroup(std::shared_ptr<Expression>,int line_start,int line_end);
            std::shared_ptr<Expression> contents;
            virtual std::string getSource() override;
            virtual void print(int depth) override;
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_GROUP_H
