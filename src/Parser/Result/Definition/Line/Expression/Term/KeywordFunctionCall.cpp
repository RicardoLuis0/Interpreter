#include "Parser/KeywordFunctionCall.h"
#include "symbols_keywords.h"
#include "Parser/ExpressionList.h"
#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

KeywordFunctionCall::KeywordFunctionCall(parserProgress &p){
    line_start=p.get_line();
    identifier=p.isKeyword({KEYWORD_IS,KEYWORD_CAST,KEYWORD_TYPEOF,KEYWORD_TYPE,KEYWORD_DECLTYPE});
    if(!identifier)throw MyExcept::NoMatchException(p,"keyword function call");
    try{
        if(p.isSymbol(SYMBOL_LOWER)){
            extra_type=std::make_shared<VarType>(p);
            if(!p.isSymbol(SYMBOL_GREATER)){
                throw MyExcept::NoMatchExceptionFatal(p,"'>'");
            }
        }
        if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
            throw MyExcept::NoMatchExceptionFatal(p,"'('");
        }
        if(!p.peekSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            arguments = std::make_shared<ExpressionList>(p);
            if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
                throw MyExcept::NoMatchExceptionFatal(p,"')'");
            }
        }
    }catch(MyExcept::NoMatchException &e){
        throw MyExcept::NoMatchExceptionFatal(e);
    }
    line_end=p.get_line(-1);
}

KeywordFunctionCall::KeywordFunctionCall(std::shared_ptr<Lexer::KeywordToken> id,std::shared_ptr<VarType> type,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id),extra_type(type),arguments(args){
    
}

std::string KeywordFunctionCall::getSource(){
    return identifier->get_literal()+(extra_type?"<"+extra_type->getSource()+">":"")+"("+arguments->getSource()+")";
}

void KeywordFunctionCall::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"KeywordFunctionCall {\n";
    std::cout<<indent0<<".identifier:\n"<<indent1<<identifier->get_formatted()<<"\n";
    if(arguments){
        std::cout<<indent0<<".arguments:\n";
        arguments->print(depth+1);
    }
    if(extra_type){
        std::cout<<indent0<<".extra_type:\n";
        extra_type->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
