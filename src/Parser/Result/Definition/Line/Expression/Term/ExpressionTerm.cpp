#include "Parser/ExpressionTerm.h"

#include <iostream>

using namespace Parser;

ExpressionTerm::ExpressionTerm(std::shared_ptr<ParserResultPart> ptr,ExpressionTermType_t ptype,int ls,int le):ParserResultPart(ls,le),contents_p(ptr),contents_t(nullptr),type(ptype){
    
}

ExpressionTerm::ExpressionTerm(std::shared_ptr<Lexer::Token> ptr,ExpressionTermType_t ptype,int ls,int le):ParserResultPart(ls,le),contents_p(nullptr),contents_t(ptr),type(ptype){
    
}

std::string ExpressionTerm::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void ExpressionTerm::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"ExpressionTerm {\n";
    std::cout<<indent0<<"}\n";
}
