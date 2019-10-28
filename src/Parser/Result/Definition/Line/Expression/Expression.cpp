#include "Parser/Expression.h"

#include <iostream>

using namespace Parser;

Expression::Expression(std::shared_ptr<ParserResultPart> ptr,ExpressionType_t ptype,int ls,int le):ParserResultPart(ls,le),contents(ptr),type(ptype){
    
}

std::string Expression::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void Expression::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"Expression {\n";
    std::cout<<indent0<<"}\n";
}
