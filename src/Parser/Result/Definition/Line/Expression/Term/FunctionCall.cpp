#include "Parser/FunctionCall.h"
#include "symbols_keywords.h"
#include "Parser/ExpressionList.h"
#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

FunctionCall::FunctionCall(parserProgress &p){
    line_start=p.get_line();
    std::shared_ptr<Lexer::Token> ident_tk=p.isType(Lexer::TOKEN_TYPE_WORD);
    if(!ident_tk) throw MyExcept::NoMatchException(p,"identifier");
    identifier=std::static_pointer_cast<Lexer::WordToken>(ident_tk)->get_literal();
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        throw MyExcept::NoMatchException(p,"'('");
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        try{
            arguments = std::make_shared<ExpressionList>(p);
        }catch(MyExcept::NoMatchException &e){
            throw MyExcept::NoMatchExceptionFatal(e);
        }
        if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            throw MyExcept::NoMatchExceptionFatal(p,"')'");
        }
    }
    line_end=p.get_line(-1);
}

FunctionCall::FunctionCall(std::string id,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id),arguments(args){
}

std::string FunctionCall::getSource(int indent){
    return identifier+"("+(arguments?arguments->getSource(indent):"")+")";
}

void FunctionCall::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"FunctionCall {\n";
    std::cout<<indent0<<".identifier:\n"<<indent1<<identifier<<"\n";
    if(arguments){
        std::cout<<indent0<<".arguments:\n";
        arguments->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}

