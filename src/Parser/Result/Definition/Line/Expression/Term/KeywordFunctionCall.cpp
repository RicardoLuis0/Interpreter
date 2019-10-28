#include "Parser/KeywordFunctionCall.h"

#include <iostream>

using namespace Parser;

KeywordFunctionCall::KeywordFunctionCall(std::shared_ptr<Lexer::KeywordToken> id,std::shared_ptr<VarType> type,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id),extra_type(type),arguments(args){
    
}

std::string KeywordFunctionCall::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void KeywordFunctionCall::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"KeywordFunctionCall {\n";
    std::cout<<indent0<<"}\n";
}
