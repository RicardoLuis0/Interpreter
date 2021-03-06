#ifndef PARSER_EXPRESSION_TERM_H
#define PARSER_EXPRESSION_TERM_H

#include <vector>
#include <memory>
#include "Parser/ParserResultPart.h"
#include "Lexer/SymbolToken.h"


namespace Parser {
    enum ExpressionTermType_t{
        EXPRESSION_TERM_EXPRESSION_GROUP,
        EXPRESSION_TERM_FUNCTION_CALL,
        EXPRESSION_TERM_KEYWORD_FUNCTION_CALL,
        EXPRESSION_TERM_UNARY_OPERATION,
        EXPRESSION_TERM_LITERAL,
        EXPRESSION_TERM_LITERAL_INT,
        EXPRESSION_TERM_LITERAL_CHAR,
        EXPRESSION_TERM_LITERAL_FLOAT,
        EXPRESSION_TERM_LITERAL_STRING,
        EXPRESSION_TERM_LITERAL_TRUE,
        EXPRESSION_TERM_LITERAL_FALSE,
        EXPRESSION_TERM_LITERAL_NULL,
        EXPRESSION_TERM_IDENTIFIER,
        EXPRESSION_TERM_VARTYPE,
    };
    enum ExpressionTermMemberAccessType_t{
        MEMBER_ACCESS_NONE,
        MEMBER_ACCESS_NORMAL,
        MEMBER_ACCESS_POINTER,
    };
    class ExpressionTerm:public ParserResultPart {
        static std::vector<int> post_unary_operators;
    public:
        ExpressionTerm(parserProgress&);
        ExpressionTerm(std::shared_ptr<ParserResultPart>,ExpressionTermType_t type,int line_start,int line_end);
        ExpressionTerm(std::shared_ptr<Lexer::Token>,ExpressionTermType_t type,int line_start,int line_end);
        std::shared_ptr<ParserResultPart> contents_p;
        std::shared_ptr<Lexer::Token> contents_t;
        std::vector<std::shared_ptr<Lexer::SymbolToken>> unary_post_operators;
        std::vector<std::shared_ptr<ParserResultPart>> array_access;//std::shared_ptr<Expression>
        ExpressionTermType_t type;
        std::shared_ptr<ExpressionTerm> member_access;
        ExpressionTermMemberAccessType_t member_access_type=MEMBER_ACCESS_NONE;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    protected:
    private:
    };
}
#endif // PARSER_EXPRESSION_TERM_H
