#include "Parser/ElseStatementMatcher.h"

#include "Parser/LineMatcher.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"

//ElseStatement = keyword 'else' , Line ;

using namespace Parser;

std::shared_ptr<ElseStatement> ElseStatementMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_ELSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'else', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    return std::make_shared<ElseStatement>(LineMatcher().makeMatch(p),line_start,p.get_line(-1));
}
