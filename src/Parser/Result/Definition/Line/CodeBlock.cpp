#include "Parser/CodeBlock.h"

#include <iostream>

using namespace Parser;

CodeBlock::CodeBlock(parserProgress &p){
    throw std::runtime_error("unimplemented");
}

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
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"CodeBlock {\n";
    if(lines.size()>0){
        std::cout<<indent0<<".lines:\n";
        for(int i=0;i<int(lines.size());i++){
            std::cout<<indent1<<".line["<<i<<"]:\n";
            lines[i]->print(depth+2);
        }
    }
    std::cout<<indent0<<"}\n";
}


