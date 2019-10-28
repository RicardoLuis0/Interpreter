#include "Parser/FunctionDefinitionParameter.h"

#include <iostream>

using namespace Parser;

FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> v,std::shared_ptr<Lexer::WordToken> i,bool ref,int ls,int le):ParserResultPart(ls,le),type(v),name(i->get_literal()),is_reference(ref){}

FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> vt,std::string n,bool ref,int ls,int le):ParserResultPart(ls,le),type(vt),name(n),is_reference(ref){}


std::string FunctionDefinitionParameter::getSource(){
    return type->getSource()+(is_reference?" & ":" ")+name;
}

void FunctionDefinitionParameter::print(int depth){
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"FunctionDefinitionParameter {\n";
    std::cout<<indent0<<".type:\n";
    type->print(depth+1);
    std::cout<<indent0<<".is_reference:\n"<<indent1<<(is_reference?"true":"false")<<"\n";
    std::cout<<indent0<<".name:\n"<<indent1<<name<<"\n"<<indent0<<".parameters:\n";
    std::cout<<indent0<<"}\n";
}
