#include "Parser/ExpressionGroup.h"
#include "MyExcept/MyExcept.h"
#include "Parser/Expression.h"
#include "symbols_keywords.h"

#include <iostream>

using namespace Parser;

ExpressionGroup::ExpressionGroup(parserProgress &p){
    line_start=p.get_line();
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    contents=std::make_shared<Expression>(p);
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
}

ExpressionGroup::ExpressionGroup(std::shared_ptr<Expression> expr,int ls,int le):ParserResultPart(ls,le),contents(expr){
    
}

std::string ExpressionGroup::getSource(){
    return "("+contents->getSource()+")";
}

void ExpressionGroup::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"ExpressionGroup {\n";
    contents->print(depth+1);
    std::cout<<indent0<<"}\n";
}
