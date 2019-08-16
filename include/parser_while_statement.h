#ifndef PARSER_WHILE_STATEMENT_H
#define PARSER_WHILE_STATEMENT_H

#include "parser_result_part.h"
#include "parser_line.h"
#include "parser_expression.h"

namespace Parser{
    class WhileStatement:public ParserResultPart{
    public:
        WhileStatement(std::shared_ptr<Expression> condition,std::shared_ptr<Line> code,int line_start,int line_end);
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Line> code;
    };
}

#endif // PARSER_WHILE_STATEMENT_H
