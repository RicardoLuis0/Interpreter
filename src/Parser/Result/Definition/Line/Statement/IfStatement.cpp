#include "Parser/IfStatement.h"

#include "Parser/Expression.h"
#include "Parser/Line.h"
#include "Parser/ElseStatement.h"

#include "symbols_keywords.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

IfStatement::IfStatement(parserProgress &p){
    line_start=p.get_line();
    if(!p.isKeyword(KEYWORD_IF)){
        throw MyExcept::NoMatchException(p,"'if'");
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        throw MyExcept::NoMatchException(p,"'('");
    }
    condition=std::make_shared<Expression>(p);
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        throw MyExcept::NoMatchException(p,"')'");
    }
    code=std::make_shared<Line>(p);
    if(p.peekKeyword(KEYWORD_ELSE)){
        else_stmt=std::make_shared<ElseStatement>(p);
    }
    line_end=p.get_line(-1);
}

IfStatement::IfStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l,std::shared_ptr<ElseStatement> es,int ls,int le):ParserResultPart(ls,le),condition(cond),code(l),else_stmt(es){
    
}

std::string IfStatement::getSource(){
    return "if("+condition->getSource()+") "+code->getSource()+(else_stmt?else_stmt->getSource():"");
}

void IfStatement::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"IfStatement {\n";
    std::cout<<indent0<<".condition:\n";
    condition->print(depth+1);
    std::cout<<indent0<<".code:\n";
    code->print(depth+1);
    if(else_stmt){
        std::cout<<indent0<<".else_stmt:\n";
        else_stmt->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
