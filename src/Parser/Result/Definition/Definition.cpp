#include "Parser/Definition.h"

#include <iostream>

using namespace Parser;

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
    std::string indent=std::string(depth*2,' ');
    std::cout<<indent<<"Definition {\n";
    def->print(depth+1);
    std::cout<<indent<<"}\n";
}
