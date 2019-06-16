#ifndef PARSER_EXPRESSION_LIST_H
#define PARSER_EXPRESSION_LIST_H

#include <vector>
#include "parser_result_part.h"
#include "parser_expression.h"

namespace Parser{
    class ExpressionList:public ParserResultPart{
    public:
        ExpressionList(std::vector<std::shared_ptr<Expression>> expression_list);
        std::vector<std::shared_ptr<Expression>> expression_list;
    };
}

#endif // PARSER_EXPRESSION_LIST_H
