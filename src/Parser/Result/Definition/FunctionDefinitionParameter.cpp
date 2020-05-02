#include "Parser/FunctionDefinitionParameter.h"

#include "Parser/VarType.h"

#include "Lexer/token_type.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

FunctionDefinitionParameter::FunctionDefinitionParameter(parserProgress &p){
    line_start=p.get_line();
    type=std::make_shared<VarType>(p);
    is_reference=p.isSymbol(SYMBOL_BITWISE_AND);
    std::shared_ptr<Lexer::Token> t;
    if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD))){
        if(is_reference){
            throw MyExcept::NoMatchExceptionFatal(p,"identifier");
        }else{
            throw MyExcept::NoMatchException(p,"identifier");
        }
    }
    name=std::static_pointer_cast<Lexer::WordToken>(t)->get_literal();
    line_end=p.get_line(-1);
}

FunctionDefinitionParameter::FunctionDefinitionParameter(int ls,std::shared_ptr<VarType> vt,parserProgress &p){
    line_start=ls;
    type=vt;
    is_reference=p.isSymbol(SYMBOL_BITWISE_AND);
    std::shared_ptr<Lexer::Token> t;
    if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD))){
        if(is_reference){
            throw MyExcept::NoMatchExceptionFatal(p,"identifier");
        }else{
            throw MyExcept::NoMatchException(p,"identifier");
        }
    }
    name=std::static_pointer_cast<Lexer::WordToken>(t)->get_literal();
    line_end=p.get_line(-1);
}

FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> v,std::shared_ptr<Lexer::WordToken> i,bool ref,int ls,int le):ParserResultPart(ls,le),type(v),name(i->get_literal()),is_reference(ref){}

FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> vt,std::string n,bool ref,int ls,int le):ParserResultPart(ls,le),type(vt),name(n),is_reference(ref){}


std::string FunctionDefinitionParameter::getSource(){
    return type->getSource()+(is_reference?" & ":" ")+name;
}

void FunctionDefinitionParameter::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"FunctionDefinitionParameter {\n";
    std::cout<<indent0<<".type:\n";
    type->print(depth+1);
    std::cout<<indent0<<".is_reference:\n"<<indent1<<(is_reference?"true":"false")<<"\n";
    std::cout<<indent0<<".name:\n"<<indent1<<name<<"\n";
    std::cout<<indent0<<"}\n";
}
