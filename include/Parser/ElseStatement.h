#ifndef PARSER_ELSE_STATEMENT_H
#define PARSER_ELSE_STATEMENT_H

#include "Parser/ResultPart.h"
#include "Parser/Line.h"

namespace Parser{
    class ElseStatement:public ParserResultPart{
    public:
        ElseStatement(std::shared_ptr<Line> code,int line_start,int line_end);
        std::shared_ptr<Line> code;
    };
}

#endif // PARSER_ELSE_STATEMENT_H