#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H

#include <vector>
#include <memory>
#include "Parser/ParserResultPart.h"
#include "Parser/ExpressionTerm.h"
#include "Parser/Expression.h"
#include "Lexer/SymbolToken.h"
#include "Lexer/KeywordToken.h"


namespace Parser{
    class BinaryOperation:public ParserResultPart{
        static std::vector<int> binary_symbol_operators;
        static std::vector<int> binary_keyword_operators;
    public:
        BinaryOperation(parserProgress&);
        BinaryOperation(std::shared_ptr<ExpressionTerm>,std::shared_ptr<Lexer::SymbolToken>,std::shared_ptr<Expression>,int line_start,int line_end);
        BinaryOperation(std::shared_ptr<ExpressionTerm>,std::shared_ptr<Lexer::KeywordToken>,std::shared_ptr<Expression>,int line_start,int line_end);
        std::shared_ptr<ExpressionTerm> term1;
        std::shared_ptr<Lexer::SymbolToken> binary_operator;
        std::shared_ptr<Lexer::KeywordToken> binary_keyword_operator;
        std::shared_ptr<Expression> term2;
        bool is_keyword;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    };
}
#endif // BINARYOPERATION_H
