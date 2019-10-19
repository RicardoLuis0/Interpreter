#ifndef PARSER_BINARY_OPERATOR_MATCHER_H
#define PARSER_BINARY_OPERATOR_MATCHER_H

#include "Parser/BaseComponent.h"
#include "Parser/BinaryOperation.h"

namespace Parser{
    class BinaryOperationMatcher:BaseComponent{
        public:
            bool checkIsBinaryOperator(parserProgress&);
            std::shared_ptr<BinaryOperation> makeMatch(parserProgress&);
    };
}

#endif // PARSER_BINARY_OPERATOR_MATCHER_H
