#ifndef PARSER_CODE_BLOCK_MATCHER_H
#define PARSER_CODE_BLOCK_MATCHER_H

#include <memory>
#include "parser_component.h"
#include "parser_code_block.h"

namespace Parser{
    class CodeBlockMatcher:BaseComponent{
        public:
            std::shared_ptr<CodeBlock> makeMatch(parserProgress&);
    };
}

#endif // PARSER_CODE_BLOCK_MATCHER_H
