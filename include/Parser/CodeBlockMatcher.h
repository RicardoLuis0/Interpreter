#ifndef PARSER_CODE_BLOCK_MATCHER_H
#define PARSER_CODE_BLOCK_MATCHER_H

#include <memory>
#include "Parser/BaseComponent.h"
#include "Parser/CodeBlock.h"

namespace Parser{
    class CodeBlockMatcher:BaseComponent{
        public:
            std::shared_ptr<CodeBlock> makeMatch(parserProgress&);
    };
}

#endif // PARSER_CODE_BLOCK_MATCHER_H
