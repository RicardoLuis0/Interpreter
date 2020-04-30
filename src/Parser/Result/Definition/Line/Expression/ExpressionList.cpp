#include "Parser/ExpressionList.h"

#include "symbols_keywords.h"

#include "Parser/Expression.h"

#include <iostream>

using namespace Parser;

ExpressionList::ExpressionList(parserProgress &p){//TODO remove expression list, move directly into FunctionCall/KeywordFunctionCall
    line_start=p.get_line();
    do{
        expression_list.emplace_back(std::make_shared<Expression>(p));
    }while(p.isSymbol(SYMBOL_COMMA));
    line_end=p.get_line(-1);
}

ExpressionList::ExpressionList(std::vector<std::shared_ptr<Expression>> el,int ls,int le):ParserResultPart(ls,le),expression_list(el){
    
}

std::string ExpressionList::getSource(){
    std::string s="";
    bool first=true;
    for(auto e:expression_list){
        if(!first){
            s+=",";
        }else{
            first=false;
        }
        s+=e->getSource();
    }
    return "";
}

void ExpressionList::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"ExpressionList {\n";
    std::cout<<indent0<<".expression_list:\n";
    for(int i=0;i<int(expression_list.size());i++){
        std::cout<<indent1<<".expr["<<i<<"]:\n";
        expression_list[i]->print(depth+2);
    }
    std::cout<<indent0<<"}\n";
}
