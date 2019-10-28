#include "Parser/UnaryOperation.h"

#include <iostream>

using namespace Parser;

UnaryOperation::UnaryOperation(std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<ExpressionTerm> et,int ls,int le):ParserResultPart(ls,le),unary_operator(st),term(et){
}

std::string UnaryOperation::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void UnaryOperation::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"UnaryOperation {\n";
    std::cout<<indent0<<"}\n";
}
