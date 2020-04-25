#include "Parser/Expression.h"

#include <iostream>

using namespace Parser;

Expression::Expression(parserProgress &p){
    throw std::runtime_error("unimplemented");
}

Expression::Expression(std::shared_ptr<ParserResultPart> ptr,ExpressionType_t ptype,int ls,int le):ParserResultPart(ls,le),contents(ptr),type(ptype){
    
}

std::string Expression::getSource(){
    return contents->getSource();
}

void Expression::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"Expression {\n";
    std::cout<<indent0<<".contents:\n";
    contents->print(depth+1);
    std::cout<<indent0<<"}\n";
}
