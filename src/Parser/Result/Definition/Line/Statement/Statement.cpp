#include "Parser/Statement.h"

#include <iostream>

using namespace Parser;

Statement::Statement(std::shared_ptr<ParserResultPart> stmt,ParserStatementType_t sttype,int ls,int le):ParserResultPart(ls,le),statement(stmt),type(sttype){
    
}

std::string Statement::getSource(){
    if(type==STATEMENT_BREAK){
        return "break;";
    }else if(STATEMENT_CONTINUE){
        return "continue;";
    }else{
        return statement->getSource();
    }
}

void Statement::print(int depth){
    std::string indent0=std::string(depth*2,' ');
    std::string indent1=std::string((depth+1)*2,' ');
    std::cout<<indent0<<"Statement {\n";
    std::cout<<indent0<<".statement:\n";
    if(type==STATEMENT_BREAK){
        std::cout<<indent1<<"break";
    }else if(STATEMENT_CONTINUE){
        std::cout<<indent1<<"continue";
    }else{
        statement->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
