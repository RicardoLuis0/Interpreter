#include "Parser/ReturnStatement.h"

#include <iostream>

using namespace Parser;

ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expr,int ls,int le):ParserResultPart(ls,le),value(expr){}

std::string ReturnStatement::getSource(){
    if(value){
        return "return "+value->getSource()+";";
    }else{
        return "return;";
    }
}

void ReturnStatement::print(int depth){
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"ReturnStatement {\n";
    std::cout<<indent0<<".value:\n";
    if(value){
        value->print(depth+1);
    }else{
        std::cout<<indent1<<"null\n";
    }
    std::cout<<indent0<<"}\n";
}
