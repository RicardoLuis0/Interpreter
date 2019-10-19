#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H

#include <memory>
#include "Parser/ResultPart.h"
#include "Parser/ExpressionTerm.h"
#include "Parser/Expression.h"
#include "Lexer/SymbolToken.h"


namespace Parser{
    class BinaryOperation:public ParserResultPart{
        public:
            BinaryOperation(std::shared_ptr<ExpressionTerm>,std::shared_ptr<Lexer::SymbolToken>,std::shared_ptr<Expression>,int line_start,int line_end);//ParserResultPart instead of Expression because of circular dependency
            std::shared_ptr<ExpressionTerm> term1;
            std::shared_ptr<Lexer::SymbolToken> binary_operator;
            std::shared_ptr<Expression> term2;
    };
}
#endif // BINARYOPERATION_H
