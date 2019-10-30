#include "Parser/ExpressionGroup.h"

#include <iostream>

using namespace Parser;

ExpressionGroup::ExpressionGroup(std::shared_ptr<Expression> expr,int ls,int le):ParserResultPart(ls,le),contents(expr){
    
}

std::string ExpressionGroup::getSource(){
    return "("+contents->getSource()+")";
}

void ExpressionGroup::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"ExpressionGroup {\n";
    contents->print(depth+1);
    std::cout<<indent0<<"}\n";
}
