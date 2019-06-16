#ifndef PARSER_FUNCTION_CALL_MATCHER_H
#define PARSER_FUNCTION_CALL_MATCHER_H

#include "parser_component.h"
#include "parser_function_call.h"

namespace Parser{
    class FunctionCallMatcher:BaseComponent{
        public:
            std::shared_ptr<FunctionCall> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_FUNCTION_CALL_MATCHER_H
