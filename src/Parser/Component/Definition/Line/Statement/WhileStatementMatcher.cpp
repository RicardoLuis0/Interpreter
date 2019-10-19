#include "Parser/WhileStatementMatcher.h"

#include "Parser/ExpressionMatcher.h"
#include "Parser/LineMatcher.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"

//WhileStatement = keyword 'while' , symbol '(' , Expression , symbol ')' , CodeBlock ;

using namespace Parser;

std::shared_ptr<WhileStatement> WhileStatementMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_WHILE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'while', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Expression> expr=ExpressionMatcher().makeMatch(p);
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Line> line=LineMatcher().makeMatch(p);
    return std::make_shared<WhileStatement>(expr,line,line_start,p.get_line(-1));
}
