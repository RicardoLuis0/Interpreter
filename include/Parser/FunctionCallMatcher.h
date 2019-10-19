#ifndef PARSER_FUNCTION_CALL_MATCHER_H
#define PARSER_FUNCTION_CALL_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/FunctionCall.h"

namespace Parser{
    class FunctionCallMatcher:BaseComponent{
        public:
            std::shared_ptr<FunctionCall> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_FUNCTION_CALL_MATCHER_H
