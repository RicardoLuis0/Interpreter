#include "Parser/FunctionCall.h"

#include <iostream>

using namespace Parser;

FunctionCall::FunctionCall(std::string id,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id),arguments(args){
}

std::string FunctionCall::getSource(){
    return identifier+"("+(arguments?arguments->getSource():"")+")";
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

