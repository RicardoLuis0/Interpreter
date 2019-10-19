#include "Parser/ReturnStatementMatcher.h"
#include "Parser/ExpressionMatcher.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"

//ReturnStatement = keyword 'return' , [ Expression ] , ';' ;

using namespace Parser;

std::shared_ptr<ReturnStatement> ReturnStatementMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_RETURN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'return', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Expression> expr;
    try{
        expr=ExpressionMatcher().makeMatch(p);
    }catch(...){
        expr=nullptr;
        if(!p.peekSymbol(SYMBOL_SEMICOLON))throw;
    }
    if(!p.isSymbol(SYMBOL_SEMICOLON))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    return std::make_shared<ReturnStatement>(expr,line_start,p.get_line(-1));
}
