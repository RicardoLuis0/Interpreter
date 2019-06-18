#include "parser_if_statment_matcher.h"

#include "parser_expression_matcher.h"
#include "parser_line_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"

//IfStatement = keyword 'if' , symbol '(' , Expression , symbol ')' , CodeBlock ;

std::shared_ptr<Parser::IfStatement> Parser::IfStatementMatcher::makeMatch(parserProgress &p){
    if(!p.isKeyword(KEYWORD_IF))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'if', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Expression> expr=ExpressionMatcher().makeMatch(p);
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Line> line=LineMatcher().makeMatch(p);
    return std::make_shared<IfStatement>(expr,line);
}
