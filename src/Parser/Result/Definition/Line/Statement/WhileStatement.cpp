#include "Parser/WhileStatement.h"

#include <iostream>

using namespace Parser;

WhileStatement::WhileStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),condition(cond),code(l){
}

std::string WhileStatement::getSource(){
    return "while("+condition->getSource()+") "+code->getSource();
}

void WhileStatement::print(int depth){
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"WhileStatement {\n";
    std::cout<<indent0<<".condition:\n";
    condition->print(depth+1);
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}
