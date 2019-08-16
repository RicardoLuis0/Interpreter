#include "parser_if_statment_matcher.h"

#include "parser_expression_matcher.h"
#include "parser_line_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"
#include "parser_else_statement_matcher.h"

//IfStatement = keyword 'if' , symbol '(' , Expression , symbol ')' , Line , [ ElseStatement ] ;

using namespace Parser;

std::shared_ptr<IfStatement> IfStatementMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_IF))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'if', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Expression> expr=ExpressionMatcher().makeMatch(p);
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Line> line=LineMatcher().makeMatch(p);
    std::shared_ptr<ElseStatement> else_stmt=nullptr;
    int location_backup=p.location;
    try{
        else_stmt=ElseStatementMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(p.isKeyword(KEYWORD_ELSE))throw;
        else_stmt=nullptr;
    }
    return std::make_shared<IfStatement>(expr,line,else_stmt,line_start,p.get_line(-1));
}
