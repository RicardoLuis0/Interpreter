#ifndef PARSER_UNARY_OPERATION_H
#define PARSER_UNARY_OPERATION_H

#include <vector>
#include <memory>
#include "Parser/ParserResultPart.h"
#include "Parser/ExpressionTerm.h"
#include "Lexer/SymbolToken.h"
#include "Lexer/KeywordToken.h"


namespace Parser{
    class UnaryOperation:public ParserResultPart{
        static std::vector<int> pre_unary_operators;
        static std::vector<int> pre_unary_keyword_operators;
    public:
        UnaryOperation(parserProgress&);
        UnaryOperation(std::shared_ptr<Lexer::SymbolToken> t_operator,std::shared_ptr<ExpressionTerm> expression_term,int line_start,int line_end);
        UnaryOperation(std::shared_ptr<Lexer::KeywordToken> t_operator,std::shared_ptr<ExpressionTerm> expression_term,int line_start,int line_end);
        std::shared_ptr<Lexer::SymbolToken> unary_operator;
        std::shared_ptr<Lexer::KeywordToken> unary_keyword_operator;
        std::shared_ptr<ExpressionTerm> term;
        bool is_keyword;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_UNARY_OPERATION_H
