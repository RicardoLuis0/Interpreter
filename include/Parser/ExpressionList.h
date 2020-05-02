#ifndef PARSER_EXPRESSION_LIST_H
#define PARSER_EXPRESSION_LIST_H

#include <vector>
#include "Parser/Expression.h"

namespace Parser{
    class ExpressionList:public ParserResultPart{
    public:
        ExpressionList(parserProgress&);
        ExpressionList(std::vector<std::shared_ptr<Expression>> expression_list,int line_start,int line_end);
        std::vector<std::shared_ptr<Expression>> expression_list;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_EXPRESSION_LIST_H
