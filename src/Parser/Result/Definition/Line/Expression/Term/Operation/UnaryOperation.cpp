#include "Parser/UnaryOperation.h"

#include <iostream>

using namespace Parser;

UnaryOperation::UnaryOperation(std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<ExpressionTerm> et,int ls,int le):ParserResultPart(ls,le),unary_operator(st),term(et),is_keyword(false){
}

UnaryOperation::UnaryOperation(std::shared_ptr<Lexer::KeywordToken> kt,std::shared_ptr<ExpressionTerm> et,int ls,int le):ParserResultPart(ls,le),unary_keyword_operator(kt),term(et),is_keyword(true){
}

std::string UnaryOperation::getSource(){
    return (is_keyword?unary_keyword_operator->get_literal():unary_operator->get_literal())+term->getSource();
}

void UnaryOperation::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"UnaryPreOperation {\n";
    std::cout<<indent0<<".unary_operator:\n"<<indent1<<unary_operator->get_formatted()<<"\n";
    std::cout<<indent0<<".term:\n";
    term->print(depth+1);
    std::cout<<indent0<<"}\n";
}
