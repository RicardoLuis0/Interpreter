#include "Parser/ElseStatement.h"

#include "Parser/Expression.h"
#include "Parser/Line.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

ElseStatement::ElseStatement(parserProgress &p){
    line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_ELSE)){
        throw MyExcept::NoMatchException(p,"'else'");
    }
    code=std::make_shared<Line>(p);
    line_end=p.get_line(-1);
}

ElseStatement::ElseStatement(std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),code(l){
    
}

std::string ElseStatement::getSource(){
    return " else "+code->getSource();
}

void ElseStatement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"ElseStatement {\n";
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}
