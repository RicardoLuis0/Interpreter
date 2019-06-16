#include "parser_expression_term.h"

Parser::ExpressionTerm::ExpressionTerm(std::shared_ptr<ParserResultPart> ptr,ExpressionTermType_t ptype):contents_p(ptr),contents_t(nullptr),type(ptype){
    
}

Parser::ExpressionTerm::ExpressionTerm(std::shared_ptr<Lexer::Token> ptr,ExpressionTermType_t ptype):contents_p(nullptr),contents_t(ptr),type(ptype){
    
}
