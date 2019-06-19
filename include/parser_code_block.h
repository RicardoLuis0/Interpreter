#ifndef PARSER_CODE_BLOCK_H
#define PARSER_CODE_BLOCK_H

#include <vector>
#include "parser_result_part.h"
#include "parser_line.h"

namespace Parser{
    class CodeBlock : public ParserResultPart {
        public:
            CodeBlock(std::vector<std::shared_ptr<Line>> lines);
            std::vector<std::shared_ptr<Line>> lines;
        protected:
        private:
    };
}

#endif // PARSER_CODE_BLOCK_H
