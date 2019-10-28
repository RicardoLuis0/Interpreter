#include "Parser/ElseStatement.h"

#include <iostream>

using namespace Parser;

ElseStatement::ElseStatement(std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),code(l){
}

std::string ElseStatement::getSource(){
    return " else "+code->getSource();
}

void ElseStatement::print(int depth){
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"ElseStatement {\n";
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}
