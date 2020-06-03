#ifndef PARSER_ELSE_STATEMENT_H
#define PARSER_ELSE_STATEMENT_H

#include "Parser/ParserResultPart.h"
#include "Parser/Line.h"

namespace Parser{
    class ElseStatement:public ParserResultPart{
    public:
        ElseStatement(parserProgress&);
        ElseStatement(std::shared_ptr<Line> code,int line_start,int line_end);
        std::shared_ptr<Line> code;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_ELSE_STATEMENT_H
