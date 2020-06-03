#include "Parser/CodeBlock.h"

#include "Parser/Line.h"

#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

CodeBlock::CodeBlock(parserProgress &p){
    line_start=p.get_line();
    if(!p.isSymbol(SYMBOL_CURLY_BRACKET_OPEN)){
        throw MyExcept::NoMatchException(p,"'{'");
    }
    try{
        while(!p.isSymbol(SYMBOL_CURLY_BRACKET_CLOSE)){
            if(!p.in_range(0)){
                throw MyExcept::NoMatchExceptionFatal(p,"'}'");
            }
            lines.emplace_back(std::make_shared<Line>(p));
        }
    }catch(MyExcept::NoMatchException &e){
        throw MyExcept::NoMatchExceptionFatal(e);
    }
    line_end=p.get_line(-1);
}

CodeBlock::CodeBlock(std::vector<std::shared_ptr<Line>> l,int ls,int le):ParserResultPart(ls,le),lines(l){
    
}

std::string CodeBlock::getSource(int indent){
    std::string c="{\n";
    std::string i_s=std::string((indent)*4,' ');
    for(auto l:lines){
        c+=i_s+"    "+l->getSource(indent+1)+"\n";
    }
    return c+i_s+"}";
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


