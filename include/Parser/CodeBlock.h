#ifndef PARSER_CODE_BLOCK_H
#define PARSER_CODE_BLOCK_H

#include <vector>
#include "Parser/ParserResultPart.h"
#include "Parser/Line.h"

namespace Parser{
    class CodeBlock : public ParserResultPart {
        public:
            CodeBlock(parserProgress&);
            CodeBlock(std::vector<std::shared_ptr<Line>> lines,int line_start,int line_end);
            std::vector<std::shared_ptr<Line>> lines;
            virtual std::string getSource(int indent) override;
            virtual void print(int depth) override;
        protected:
        private:
    };
}

#endif // PARSER_CODE_BLOCK_H
