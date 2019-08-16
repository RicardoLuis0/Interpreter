#ifndef PARSER_IF_STATEMENT_H
#define PARSER_IF_STATEMENT_H

#include "parser_result_part.h"
#include "parser_line.h"
#include "parser_expression.h"
#include "parser_else_statement.h"

namespace Parser{
    class IfStatement:public ParserResultPart{
    public:
        IfStatement(std::shared_ptr<Expression> condition,std::shared_ptr<Line> code,std::shared_ptr<ElseStatement> else_stmt,int line_start,int line_end);
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Line> code;
        std::shared_ptr<ElseStatement> else_stmt;
    };
}

#endif // PARSER_IF_STATEMENT_H
