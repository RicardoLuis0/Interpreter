#ifndef PARSER_UNARY_OPERATION_MATCHER_H
#define PARSER_UNARY_OPERATION_MATCHER_H

#include "parser_component.h"
#include "parser_unary_operation.h"

namespace Parser{
    class UnaryOperationMatcher:BaseComponent{
        public:
            bool checkIsPreUnaryOperator(parserProgress&);
            bool checkIsPostUnaryOperator(parserProgress&);
            std::shared_ptr<UnaryOperation> makeMatch(parserProgress&);
        protected:
        private:
    };
}
#endif // PARSER_UNARY_OPERATION_MATCHER_H
