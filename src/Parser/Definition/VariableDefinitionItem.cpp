#include "Parser/VariableDefinitionItem.h"

#include "Parser/Expression.h"

#include "Lexer/token_type.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

VariableDefinitionItem::VariableDefinitionItem(parserProgress &p){
    line_start=p.get_line();
    std::shared_ptr<Lexer::Token> t=p.isType(Lexer::TOKEN_TYPE_WORD);
    if(!t){
        throw MyExcept::NoMatchException(p,"identifier");
    }
    name=std::static_pointer_cast<Lexer::WordToken>(t)->get_literal();
    if(p.isSymbol(SYMBOL_ASSIGNMENT)){
        value=std::make_shared<Expression>(p);
    }
    line_end=p.get_line(-1);
}

VariableDefinitionItem::VariableDefinitionItem(int ls,std::shared_ptr<Lexer::WordToken> t,parserProgress &p){
    line_start=ls;
    name=t->get_literal();
    if(p.isSymbol(SYMBOL_ASSIGNMENT)){
        value=std::make_shared<Expression>(p);
    }
    line_end=p.get_line(-1);
}

VariableDefinitionItem::VariableDefinitionItem(std::string s,int ls,int le):ParserResultPart(ls,le),name(s),value(nullptr){
}

VariableDefinitionItem::VariableDefinitionItem(std::shared_ptr<Lexer::WordToken> t,std::shared_ptr<Expression> e,int ls,int le):ParserResultPart(ls,le),name(t->get_literal()),value(e){
}

std::string VariableDefinitionItem::getSource(int indent){
    if(value){
        return name+"="+value->getSource(indent);
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
