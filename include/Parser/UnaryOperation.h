#ifndef PARSER_UNARY_OPERATION_H
#define PARSER_UNARY_OPERATION_H

#include <memory>
#include "Parser/ParserResultPart.h"
#include "Parser/ExpressionTerm.h"
#include "Lexer/SymbolToken.h"


namespace Parser{
    class UnaryOperation:public ParserResultPart{
    public:
        UnaryOperation(std::shared_ptr<Lexer::SymbolToken> t_operator,std::shared_ptr<ExpressionTerm> expression_term,int line_start,int line_end);
        std::shared_ptr<Lexer::SymbolToken> unary_operator;
        std::shared_ptr<ExpressionTerm> term;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_UNARY_OPERATION_H
