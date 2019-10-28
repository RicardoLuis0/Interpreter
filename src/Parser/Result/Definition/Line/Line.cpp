#include "Parser/Line.h"

#include <iostream>

using namespace Parser;

Line::Line(std::shared_ptr<ParserResultPart> ptr,ParserLineType_t ptype,int ls,int le):ParserResultPart(ls,le),contents(ptr),type(ptype){
    
}

std::string Line::getSource(){
    if(type==LINE_EMPTY){
        return ";";
    }else if(type==LINE_EXPRESSION){
        return contents->getSource()+";";
    }else{
        return contents->getSource();
    }
}

void Line::print(int depth){
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"Line {\n";
    std::cout<<indent0<<".content:\n";
    if(type==LINE_EMPTY){
        std::cout<<indent1<<"null\n";
    }else{
        contents->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
