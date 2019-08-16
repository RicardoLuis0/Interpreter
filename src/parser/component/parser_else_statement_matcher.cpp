#include "parser_else_statement_matcher.h"

#include "parser_line_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"

//ElseStatement = keyword 'else' , Line ;

using namespace Parser;

std::shared_ptr<ElseStatement> ElseStatementMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_ELSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'else', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    return std::make_shared<ElseStatement>(LineMatcher().makeMatch(p),line_start,p.get_line(-1));
}
