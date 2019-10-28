#include "Parser/CodeBlock.h"

#include <iostream>

using namespace Parser;

CodeBlock::CodeBlock(std::vector<std::shared_ptr<Line>> l,int ls,int le):ParserResultPart(ls,le),lines(l){
}

std::string CodeBlock::getSource(){
    std::string c="{\n";
    for(auto l:lines){
        c+=l->getSource()+"\n";
    }
    return c+"}";
}

void CodeBlock::print(int depth){
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"CodeBlock {\n";
    std::cout<<indent0<<".lines:\n";
    for(int i=0;i<int(lines.size());i++){
        std::cout<<indent1<<".line["<<i<<"]:";
        lines[i]->print(depth+2);
    }
    std::cout<<indent0<<"}\n";
}


