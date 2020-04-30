#include "Parser/UnaryOperation.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

std::vector<int> UnaryOperation::pre_unary_operators{//these can also be binary operators
    SYMBOL_PLUS,
    SYMBOL_MINUS,
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
    SYMBOL_LOGICAL_NOT,
    SYMBOL_BITWISE_AND,
    SYMBOL_MULTIPLY,
};

std::vector<int> UnaryOperation::pre_unary_keyword_operators {
    KEYWORD_TYPEOF,
};

UnaryOperation::UnaryOperation(parserProgress &p){
    line_start=p.get_line();
    is_keyword=true;
    if(!(unary_keyword_operator=p.isKeyword(pre_unary_keyword_operators))){
        is_keyword=false;
        if(!(unary_operator=p.isSymbol(pre_unary_operators))){
            throw MyExcept::NoMatchException(p,"unary operator");
        }
    }
    term=std::make_shared<ExpressionTerm>(p);
    line_end=p.get_line(-1);
}

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
