#ifndef PARSER_UNARY_OPERATION_H
#define PARSER_UNARY_OPERATION_H

#include <memory>
#include "parser_result_part.h"
#include "parser_expression_term.h"
#include "symbol_token.h"

namespace Parser{
    class UnaryOperation:public ParserResultPart{
    public:
        UnaryOperation(std::shared_ptr<Lexer::SymbolToken> t_operator,std::shared_ptr<ExpressionTerm> expression_term,int line_start,int line_end);
        std::shared_ptr<Lexer::SymbolToken> unary_operator;
        std::shared_ptr<ExpressionTerm> term;
    };
}

#endif // PARSER_UNARY_OPERATION_H
