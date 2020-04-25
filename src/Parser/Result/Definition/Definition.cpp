#include "Parser/Definition.h"

#include <iostream>

using namespace Parser;

Definition::Definition(parserProgress &p){
    throw std::runtime_error("unimplemented");
}

Definition::Definition(ParserDefinitionType_t t,std::shared_ptr<ParserResultPart> d,int ls,int le):ParserResultPart(ls,le),type(t),def(d){
    
}

std::string Definition::getSource(){
    if(type==DEFINITION_VAR){
        return def->getSource()+";";
    }else{
        return def->getSource();
    }
}

void Definition::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"Definition {\n";
    def->print(depth+1);
    std::cout<<indent0<<"}\n";
}
