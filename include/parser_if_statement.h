#ifndef PARSER_IF_STATEMENT_H
#define PARSER_IF_STATEMENT_H

#include "parser_result_part.h
#include "parser_line.h"
#include "parser_expression.h"

namespace Parser{
    class IfStatement:public ParserResultPart{
    public:
        IfStatement(std::shared_ptr<Expression> condition,std::shared_ptr<Line> code);
    };
}

#endif // PARSER_IF_STATEMENT_H
