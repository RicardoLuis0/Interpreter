#include "parser_else_statement_matcher.h"

#include "parser_line_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"

//ElseStatement = keyword 'else' , Line ;

std::shared_ptr<Parser::ElseStatement> Parser::ElseStatementMatcher::makeMatch(parserProgress &p){
    if(!p.isKeyword(KEYWORD_ELSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'else', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    return std::make_shared<ElseStatement>(LineMatcher().makeMatch(p));
}
