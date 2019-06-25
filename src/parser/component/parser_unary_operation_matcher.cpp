#include "parser_unary_operation_matcher.h"
#include "symbols_keywords.h"
#include "parser_expression_term_matcher.h"
#include "my_except.h"

//UnaryOperation = symbol 'any_unary_operator' , ExpressionTerm;

static std::vector<int> pre_unary_operators{//these might also be binary operators
    SYMBOL_PLUS,
    SYMBOL_MINUS,
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
};

/*
static std::vector<int> post_unary_operators{//these must not be binary operators
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
};
*/

bool Parser::UnaryOperationMatcher::checkIsPreUnaryOperator(parserProgress &p){
    return p.peekSymbol(pre_unary_operators);
}

/*
bool Parser::UnaryOperationMatcher::checkIsPostUnaryOperator(parserProgress &p){
    return p.peekSymbol(post_unary_operators);
}
*/

std::shared_ptr<Parser::UnaryOperation> Parser::UnaryOperationMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<Lexer::SymbolToken> op=p.isSymbol(pre_unary_operators);
    if(!op){
        throw MyExcept::NoMatchException(0,"");//this isn't shown
    }else{
        return std::make_shared<UnaryOperation>(op,ExpressionTermMatcher().makeMatch(p));
    }
}
