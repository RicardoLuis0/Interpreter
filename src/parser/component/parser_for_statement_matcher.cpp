#include "parser_for_statement_matcher.h"

#include "parser_expression_matcher.h"
#include "parser_line_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"

std::shared_ptr<Parser::ForStatement> Parser::ForStatementMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<Expression> pre,cond,inc;
    if(!p.isKeyword(KEYWORD_FOR))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'for', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    int location_backup=p.location;
    try{
        pre=ExpressionMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_SEMICOLON))throw;//if next symbol isn't a semicolon, rethrow
        pre=nullptr;
    }
    if(!p.isSymbol(SYMBOL_SEMICOLON))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    location_backup=p.location;
    try{
        cond=ExpressionMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_SEMICOLON))throw;//if next symbol isn't a semicolon, rethrow
        cond=nullptr;
    }
    if(!p.isSymbol(SYMBOL_SEMICOLON))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    location_backup=p.location;
    try{
        inc=ExpressionMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_PARENTHESIS_CLOSE))throw;//if next symbol isn't a ')', rethrow
        inc=nullptr;
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Line> line=LineMatcher().makeMatch(p);
    return std::make_shared<ForStatement>(pre,cond,inc,line);
}
