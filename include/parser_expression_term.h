#ifndef PARSER_EXPRESSION_TERM_H
#define PARSER_EXPRESSION_TERM_H

#include <memory>
#include "parser_result_part.h"
#include "token.h"

namespace Parser {
    enum ExpressionTermType_t{
        EXPRESSION_TERM_EXPRESSION_GROUP,
        EXPRESSION_TERM_FUNCTION_CALL,
        EXPRESSION_TERM_UNARY_OPERATION,
        EXPRESSION_TERM_LITERAL_INT,
        EXPRESSION_TERM_LITERAL_FLOAT,
        EXPRESSION_TERM_LITERAL_STRING,
        EXPRESSION_TERM_IDENTIFIER,
    };
    class ExpressionTerm:public ParserResultPart {
        public:
            ExpressionTerm(std::shared_ptr<ParserResultPart>,ExpressionTermType_t type);
            ExpressionTerm(std::shared_ptr<Lexer::Token>,ExpressionTermType_t type);
            std::shared_ptr<ParserResultPart> contents_p;
            std::shared_ptr<Lexer::Token> contents_t;
            const ExpressionTermType_t type;
        protected:
        private:
    };
}
#endif // PARSER_EXPRESSION_TERM_H
