#include "Parser/FunctionCall.h"

#include <iostream>

using namespace Parser;

FunctionCall::FunctionCall(std::string id,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id),arguments(args){
}

std::string FunctionCall::getSource(){
    throw std::runtime_error("unimplemented");
    return "";
}

void FunctionCall::print(int depth){
    throw std::runtime_error("unimplemented");
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"FunctionCall {\n";
    std::cout<<indent0<<"}\n";
}

