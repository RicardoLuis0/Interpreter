#include "Parser/VariableDefinitionItem.h"

#include <iostream>

using namespace Parser;

VariableDefinitionItem::VariableDefinitionItem(parserProgress &p){
    throw std::runtime_error("unimplemented");
}

VariableDefinitionItem::VariableDefinitionItem(std::string s,int ls,int le):ParserResultPart(ls,le),name(s),value(nullptr){
}

VariableDefinitionItem::VariableDefinitionItem(std::shared_ptr<Lexer::WordToken> t,std::shared_ptr<Expression> e,int ls,int le):ParserResultPart(ls,le),name(t->get_literal()),value(e){
}

std::string VariableDefinitionItem::getSource(){
    if(value){
        return name+"="+value->getSource();
    }else{
        return name;
    }
}

void VariableDefinitionItem::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"VariableDefinitionItem {\n";
    std::cout<<indent0<<".name:\n"<<indent1<<name<<"\n";
    if(value){
        std::cout<<indent0<<".value:\n";
        value->print(depth+1);
    }else{
        std::cout<<indent0<<".value:\n"<<indent1<<"null\n";
    }
    std::cout<<indent0<<"}\n";
}
