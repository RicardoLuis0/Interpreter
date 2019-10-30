#include "Parser/WhileStatement.h"

#include <iostream>

using namespace Parser;

WhileStatement::WhileStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),condition(cond),code(l){
}

std::string WhileStatement::getSource(){
    return "while("+condition->getSource()+") "+code->getSource();
}

void WhileStatement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"WhileStatement {\n";
    std::cout<<indent0<<".condition:\n";
    condition->print(depth+1);
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}
