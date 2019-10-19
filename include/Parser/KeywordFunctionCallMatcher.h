#ifndef PARSER_KEYWORD_FUNCTION_CALL_MATCHER_H
#define PARSER_KEYWORD_FUNCTION_CALL_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/KeywordFunctionCall.h"

namespace Parser {
    class KeywordFunctionCallMatcher : public BaseComponent {
        public:
            std::shared_ptr<KeywordFunctionCall> makeMatch(parserProgress &p);
    };
}

#endif // PARSER_KEYWORD_FUNCTION_CALL_MATCHER_H
