#include "parser_unary_operation_matcher.h"
#include "symbols_keywords.h"
#include "parser_expression_term_matcher.h"
#include "my_except.h"

//UnaryOperation = symbol 'any_unary_operator' , ExpressionTerm;

using namespace Parser;

std::vector<int> UnaryOperationMatcher::pre_unary_operators{//these might also be binary operators
    SYMBOL_PLUS,
    SYMBOL_MINUS,
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
    SYMBOL_LOGICAL_NOT,
};

std::vector<int> UnaryOperationMatcher::post_unary_operators{//these must not be binary operators
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
};

bool UnaryOperationMatcher::checkIsPreUnaryOperator(parserProgress &p){
    return p.peekSymbol(pre_unary_operators);
}

std::shared_ptr<UnaryOperation> UnaryOperationMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Lexer::SymbolToken> op=p.isSymbol(pre_unary_operators);
    if(!op){
        throw MyExcept::NoMatchException(0,"");//this isn't shown
    }else{
        return std::make_shared<UnaryOperation>(op,ExpressionTermMatcher().makeMatch(p),line_start,p.get_line(-1));
    }
}
