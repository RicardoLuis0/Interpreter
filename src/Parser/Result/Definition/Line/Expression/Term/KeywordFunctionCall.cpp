#include "Parser/KeywordFunctionCall.h"

#include <iostream>

using namespace Parser;

KeywordFunctionCall::KeywordFunctionCall(parserProgress &p){
    throw std::runtime_error("unimplemented");
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
