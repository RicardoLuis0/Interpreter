#include "Parser/BinaryOperation.h"

#include <iostream>

using namespace Parser;

BinaryOperation::BinaryOperation(std::shared_ptr<ExpressionTerm> et,std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<Expression> ex,int ls,int le):ParserResultPart(ls,le),term1(et),binary_operator(st),term2(ex){
    
}

std::string BinaryOperation::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void BinaryOperation::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"BinaryOperation {\n";
    std::cout<<indent0<<"}\n";
}
