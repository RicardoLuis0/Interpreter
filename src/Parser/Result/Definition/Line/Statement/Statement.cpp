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
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"Statement {\n";
    if(type==STATEMENT_BREAK){
        std::cout<<indent0<<".type:\n"<<indent1<<"STATEMENT_BREAK\n";
    }else if(STATEMENT_CONTINUE){
        std::cout<<indent0<<".type:\n"<<indent1<<"STATEMENT_CONTINUE\n";
    }else{
        std::cout<<indent0<<".statement:\n";
        statement->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
