#include "Parser/ExpressionTerm.h"

using namespace Parser;

ExpressionTerm::ExpressionTerm(std::shared_ptr<ParserResultPart> ptr,ExpressionTermType_t ptype,int ls,int le):ParserResultPart(ls,le),contents_p(ptr),contents_t(nullptr),type(ptype){
    
}

ExpressionTerm::ExpressionTerm(std::shared_ptr<Lexer::Token> ptr,ExpressionTermType_t ptype,int ls,int le):ParserResultPart(ls,le),contents_p(nullptr),contents_t(ptr),type(ptype){
    
}
