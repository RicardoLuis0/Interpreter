#ifndef PARSER_LINE_H
#define PARSER_LINE_H

#include <memory>
#include "parser_result_part.h"

namespace Parser{
    enum ParserLineType_t{
        LINE_CODE_BLOCK,
        LINE_STATEMENT,
        LINE_EXPRESSION,
    };
    class Line : public ParserResultPart {
        public://TODO finish line
            Line(std::shared_ptr<ParserResultPart>,ParserLineType_t);
            std::shared_ptr<ParserResultPart> contents;
            const ParserLineType_t type;
        protected:
        private:
    };
}

#endif // PARSER_LINE_H
