#ifndef PARSER_RESULT_PART_H
#define PARSER_RESULT_PART_H

#include <string>
#include "Parser/Parser.h"

namespace Parser{
    class ParserResultPart{
    public:
        ParserResultPart();
        ParserResultPart(int line_start,int line_end);
        virtual std::string getSource(int indent)=0;
        virtual void print(int depth)=0;
        int line_start;
        int line_end;
    protected:
        std::string get_indent(int depth);
    private:
    };
}

#endif // PARSER_RESULT_PART_H
