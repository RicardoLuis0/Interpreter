#include "Parser/ExpressionGroup.h"

#include <iostream>

using namespace Parser;

ExpressionGroup::ExpressionGroup(std::shared_ptr<Expression> expr,int ls,int le):ParserResultPart(ls,le),contents(expr){
    
}

std::string ExpressionGroup::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void ExpressionGroup::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"ExpressionGroup {\n";
    std::cout<<indent0<<"}\n";
}
