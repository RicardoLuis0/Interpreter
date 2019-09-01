#ifndef PARSER_KEYWORD_FUNCTION_CALL_MATCHER_H
#define PARSER_KEYWORD_FUNCTION_CALL_MATCHER_H

#include "parser_component.h"
#include "parser_keyword_function_call.h"

namespace Parser {
    class KeywordFunctionCallMatcher : public BaseComponent {
        public:
            std::shared_ptr<KeywordFunctionCall> makeMatch(parserProgress &p);
    };
}

#endif // PARSER_KEYWORD_FUNCTION_CALL_MATCHER_H
