#include "Parser/ElseStatement.h"

#include <iostream>

using namespace Parser;

ElseStatement::ElseStatement(parserProgress &p){
    throw std::runtime_error("unimplemented");
}

ElseStatement::ElseStatement(std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),code(l){
}

std::string ElseStatement::getSource(){
    return " else "+code->getSource();
}

void ElseStatement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"ElseStatement {\n";
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}
