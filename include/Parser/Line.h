#ifndef PARSER_LINE_H
#define PARSER_LINE_H

#include <memory>
#include "Parser/ParserResultPart.h"

namespace Parser{
    enum ParserLineType_t{
        LINE_CODE_BLOCK,
        LINE_STATEMENT,
        LINE_EXPRESSION,
        LINE_DEFINITION,
        LINE_EMPTY,
    };
    class Line : public ParserResultPart {
    public:
        Line(parserProgress&);
        Line(std::shared_ptr<ParserResultPart>,ParserLineType_t,int line_start,int line_end);
        std::shared_ptr<ParserResultPart> contents;
        ParserLineType_t type;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    protected:
    private:
    };
}

#endif // PARSER_LINE_H
