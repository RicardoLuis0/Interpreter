#ifndef PARSER_ELSE_STATEMENT_H
#define PARSER_ELSE_STATEMENT_H

#include "parser_result_part.h"
#include "parser_line.h"

namespace Parser{
    class ElseStatement:public ParserResultPart{
    public:
        ElseStatement(std::shared_ptr<Line> code);
        std::shared_ptr<Line> code;
    };
}

#endif // PARSER_ELSE_STATEMENT_H
