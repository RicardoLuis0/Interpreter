#ifndef BINARYOPERATION_H
#define BINARYOPERATION_H

#include <memory>
#include "parser_result_part.h"
#include "parser_expression_term.h"
#include "parser_expression.h"
#include "symbol_token.h"

namespace Parser{
    class BinaryOperation:public ParserResultPart{
        public:
            BinaryOperation(std::shared_ptr<ExpressionTerm>,std::shared_ptr<Lexer::SymbolToken>,std::shared_ptr<Expression>);//ParserResultPart instead of Expression because of circular dependency
            std::shared_ptr<ExpressionTerm> term1;
            std::shared_ptr<Lexer::SymbolToken> binary_operator;
            std::shared_ptr<Expression> term2;
    };
}
#endif // BINARYOPERATION_H
