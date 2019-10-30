#include "Parser/BinaryOperation.h"

#include <iostream>

using namespace Parser;

BinaryOperation::BinaryOperation(std::shared_ptr<ExpressionTerm> et,std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<Expression> ex,int ls,int le):ParserResultPart(ls,le),term1(et),binary_operator(st),term2(ex){
    
}

std::string BinaryOperation::getSource(){
    return term1->getSource()+binary_operator->get_literal()+term2->getSource();
}

void BinaryOperation::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"BinaryOperation {\n";
    std::cout<<indent0<<".term1:\n";
    term1->print(depth+1);
    std::cout<<indent0<<".binary_operator:\n"<<indent1<<binary_operator->get_formatted()<<"\n";
    std::cout<<indent0<<".term2:\n";
    term2->print(depth+1);
    std::cout<<indent0<<"}\n";
}
