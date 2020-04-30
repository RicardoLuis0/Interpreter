#include "Parser/WhileStatement.h"

#include "Parser/Expression.h"
#include "Parser/Line.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

WhileStatement::WhileStatement(parserProgress &p){
    line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_WHILE)){
        throw MyExcept::NoMatchException(p,"'while'");
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        throw MyExcept::NoMatchException(p,"'('");
    }
    condition=std::make_shared<Expression>(p);
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        throw MyExcept::NoMatchException(p,"')'");
    }
    code=std::make_shared<Line>(p);
    line_end=p.get_line(-1);
}

WhileStatement::WhileStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),condition(cond),code(l){
    
}

std::string WhileStatement::getSource(){
    return "while("+condition->getSource()+") "+code->getSource();
}

void WhileStatement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"WhileStatement {\n";
    std::cout<<indent0<<".condition:\n";
    condition->print(depth+1);
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    std::cout<<indent0<<"}\n";
}
