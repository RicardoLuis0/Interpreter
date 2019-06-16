#include "parser_statement_matcher.h"
#include "my_except.h"

//Statement = IfStatement | WhileStatement | ForStatement ;

std::shared_ptr<Parser::Statement> Parser::StatementMatcher::makeMatch(parserProgress &p){
    throw std::runtime_error("unimplemented");
    //TODO
}
