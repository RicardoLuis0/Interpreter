#ifndef PARSEREXPRESSION_H
#define PARSEREXPRESSION_H

#include <memory>
#include "parser_result_part.h"

namespace Parser{
    enum ExpressionType_t{
        EXPRESSION_BINARY_OPERATION,
        EXPRESSION_TERM,
    };
    class Expression:public ParserResultPart {
        public:
            Expression(std::shared_ptr<ParserResultPart>,ExpressionType_t type,int line_start,int line_end);
            std::shared_ptr<ParserResultPart> contents;
            const ExpressionType_t type;
        protected:
        private:
    };
}

#endif // PARSEREXPRESSION_H
