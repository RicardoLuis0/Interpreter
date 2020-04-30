#include "Parser/ReturnStatement.h"

#include "Parser/Expression.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

ReturnStatement::ReturnStatement(parserProgress &p){
    line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_RETURN)){
        throw MyExcept::NoMatchException(p,"'return'");
    }
    if(!p.isSymbol(SYMBOL_SEMICOLON)){
        value=std::make_shared<Expression>(p);
        if(!p.isSymbol(SYMBOL_SEMICOLON)){
            throw MyExcept::NoMatchException(p,"';'");
        }
    }
    line_end=p.get_line(-1);
}

ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expr,int ls,int le):ParserResultPart(ls,le),value(expr){
    
}

std::string ReturnStatement::getSource(){
    if(value){
        return "return "+value->getSource()+";";
    }else{
        return "return;";
    }
}

void ReturnStatement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"ReturnStatement {\n";
    std::cout<<indent0<<".value:\n";
    if(value){
        value->print(depth+1);
    }else{
        std::cout<<indent1<<"null\n";
    }
    std::cout<<indent0<<"}\n";
}
