#include "Parser/UnaryOperationMatcher.h"
#include "symbols_keywords.h"
#include "Parser/ExpressionTermMatcher.h"
#include "MyExcept/MyExcept.h"

//UnaryOperation = symbol 'any_unary_operator' , ExpressionTerm;

using namespace Parser;

std::vector<int> UnaryOperationMatcher::post_unary_operators{//these must not be binary operators
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
};

std::vector<int> UnaryOperationMatcher::pre_unary_operators{//these might also be binary operators
    SYMBOL_PLUS,
    SYMBOL_MINUS,
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
    SYMBOL_LOGICAL_NOT,
    SYMBOL_BITWISE_AND,
    SYMBOL_MULTIPLY,
};

std::vector<int> UnaryOperationMatcher::pre_unary_keyword_operators {
    KEYWORD_TYPEOF,
};

bool UnaryOperationMatcher::checkIsPreUnaryOperator(parserProgress &p){
    return p.peekSymbol(pre_unary_operators);
}

std::shared_ptr<UnaryOperation> UnaryOperationMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Lexer::KeywordToken> kptr;
    std::shared_ptr<Lexer::SymbolToken> sptr;
    if(!(kptr=p.isKeyword(pre_unary_keyword_operators))){
        if(!(sptr=p.isSymbol(pre_unary_operators))){
            throw MyExcept::NoMatchException(0,"");//this isn't shown
        }
    }
    if(sptr){
        return std::make_shared<UnaryOperation>(sptr,ExpressionTermMatcher().makeMatch(p),line_start,p.get_line(-1));
    }else{
        return std::make_shared<UnaryOperation>(kptr,ExpressionTermMatcher().makeMatch(p),line_start,p.get_line(-1));
    }
}
