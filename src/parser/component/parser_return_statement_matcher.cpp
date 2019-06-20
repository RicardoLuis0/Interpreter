#include "parser_return_statement_matcher.h"
#include "parser_expression_matcher.h"
#include "symbols_keywords.h"
#include "my_except.h"

//ReturnStatement = keyword 'return' , Expression ;

std::shared_ptr<Parser::ReturnStatement> Parser::ReturnStatementMatcher::makeMatch(parserProgress &p){
    if(!p.isKeyword(KEYWORD_RETURN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'return', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    return std::make_shared<ReturnStatement>(ExpressionMatcher().makeMatch(p));
}
