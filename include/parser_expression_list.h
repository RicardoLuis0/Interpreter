#ifndef PARSER_EXPRESSION_LIST_H
#define PARSER_EXPRESSION_LIST_H

#include <vector>
#include "parser_result_part.h"
#include "parser_expression.h"

namespace Parser{
    class ExpressionList:public ParserResultPart{
    public:
        ExpressionList(std::vector<std::shared_ptr<Expression>> expression_list,int line_start,int line_end);
        std::vector<std::shared_ptr<Expression>> expression_list;
    };
}

#endif // PARSER_EXPRESSION_LIST_H
