#include "Parser/ExpressionList.h"

#include <iostream>

using namespace Parser;

ExpressionList::ExpressionList(std::vector<std::shared_ptr<Expression>> el,int ls,int le):ParserResultPart(ls,le),expression_list(el){
    
}

std::string ExpressionList::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void ExpressionList::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"ExpressionList {\n";
    std::cout<<indent0<<"}\n";
}
