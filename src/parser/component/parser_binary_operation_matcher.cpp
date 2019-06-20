#include "parser_binary_operation_matcher.h"

#include "parser_expression_term_matcher.h"
#include "parser_expression_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"

//BinaryOperation = ExpressionTerm , binary_operator , Expression ;

static std::vector<int> binary_operators{
    SYMBOL_ASSIGNMENT,
    SYMBOL_EQUALS,
    SYMBOL_NOT_EQUALS,
    SYMBOL_GREATER,
    SYMBOL_GREATER_EQUALS,
    SYMBOL_LOWER,
    SYMBOL_LOWER_EQUALS,
    SYMBOL_PLUS,
    SYMBOL_PLUS_ASSIGNMENT,
    SYMBOL_MINUS,
    SYMBOL_MINUS_ASSIGNMENT,
    SYMBOL_MULTIPLY,
    SYMBOL_MULTIPLY_ASSIGNMENT,
    SYMBOL_DIVIDE,
    SYMBOL_DIVIDE_ASSIGNMENT,
    SYMBOL_LOGICAL_AND,
    SYMBOL_LOGICAL_OR,
    SYMBOL_BITWISE_AND,
    SYMBOL_BITWISE_AND_ASSIGNMENT,
    SYMBOL_BITWISE_OR,
    SYMBOL_BITWISE_OR_ASSIGNMENT,
    SYMBOL_BITWISE_XOR,
    SYMBOL_BITWISE_XOR_ASSIGNMENT,
    SYMBOL_LEFT_SHIFT,
    SYMBOL_LEFT_SHIFT_ASSIGNMENT,
    SYMBOL_RIGHT_SHIFT,
    SYMBOL_RIGHT_SHIFT_ASSIGNMENT,
    SYMBOL_PERCENT,
    SYMBOL_PERCENT_ASSIGNMENT,
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
