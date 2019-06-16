#include "parser_binary_operation_matcher.h"

#include "parser_expression_term_matcher.h"
#include "parser_expression_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"

//BinaryOperation = ExpressionTerm , binary_operator , Expression ;

static std::vector<int> binary_operators{
    SYMBOL_PLUS,
    SYMBOL_MINUS,
    SYMBOL_MULTIPLY,
    SYMBOL_DIVIDE,
};

bool Parser::BinaryOperationMatcher::checkIsBinaryOperator(parserProgress &p){
    return p.peekSymbol(binary_operators);
}

std::shared_ptr<Parser::BinaryOperation> Parser::BinaryOperationMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<ExpressionTerm> term1=ExpressionTermMatcher().makeMatch(p);
    std::shared_ptr<Lexer::SymbolToken> ptr=p.isSymbol(binary_operators);
    if(!ptr){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected binary operator, got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    std::shared_ptr<Expression> term2=ExpressionMatcher().makeMatch(p);
    return std::make_shared<BinaryOperation>(term1,ptr,term2);
}
