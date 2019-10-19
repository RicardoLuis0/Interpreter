#ifndef PARSER_CODE_BLOCK_H
#define PARSER_CODE_BLOCK_H

#include <vector>
#include "Parser/ResultPart.h"
#include "Parser/Line.h"

namespace Parser{
    class CodeBlock : public ParserResultPart {
        public:
            CodeBlock(std::vector<std::shared_ptr<Line>> lines,int line_start,int line_end);
            std::vector<std::shared_ptr<Line>> lines;
        protected:
        private:
    };
}

#endif // PARSER_CODE_BLOCK_H
