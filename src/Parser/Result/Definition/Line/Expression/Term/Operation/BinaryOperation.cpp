#include "Parser/BinaryOperation.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

std::vector<int> BinaryOperation::binary_symbol_operators{
    SYMBOL_ASSIGNMENT,
    SYMBOL_EQUALS,
    SYMBOL_NOT_EQUALS,
    SYMBOL_GREATER,
    SYMBOL_GREATER_EQUALS,
    SYMBOL_LOWER,
    SYMBOL_LOWER_EQUALS,
    SYMBOL_PLUS,
    SYMBOL_PLUS_ASSIGNMENT,
    SYMBOL_MINUS,
    SYMBOL_MINUS_ASSIGNMENT,
    SYMBOL_MULTIPLY,
    SYMBOL_MULTIPLY_ASSIGNMENT,
    SYMBOL_DIVIDE,
    SYMBOL_DIVIDE_ASSIGNMENT,
    SYMBOL_LOGICAL_AND,
    SYMBOL_LOGICAL_OR,
    SYMBOL_BITWISE_AND,
    SYMBOL_BITWISE_AND_ASSIGNMENT,
    SYMBOL_BITWISE_OR,
    SYMBOL_BITWISE_OR_ASSIGNMENT,
    SYMBOL_BITWISE_XOR,
    SYMBOL_BITWISE_XOR_ASSIGNMENT,
    SYMBOL_LEFT_SHIFT,
    SYMBOL_LEFT_SHIFT_ASSIGNMENT,
    SYMBOL_RIGHT_SHIFT,
    SYMBOL_RIGHT_SHIFT_ASSIGNMENT,
    SYMBOL_PERCENT,
    SYMBOL_PERCENT_ASSIGNMENT,
};

std::vector<int> BinaryOperation::binary_keyword_operators{
    KEYWORD_IS,
};

BinaryOperation::BinaryOperation(parserProgress &p){
    line_start=p.get_line();
    term1=std::make_shared<ExpressionTerm>(p);
    is_keyword=true;
    if(!(binary_keyword_operator=p.isKeyword(binary_keyword_operators))){
        is_keyword=false;
        if(!(binary_operator=p.isSymbol(binary_symbol_operators))){
            throw MyExcept::NoMatchException(p,"binary operator");
        }
    }
    term2=std::make_shared<Expression>(p);
    line_end=p.get_line(-1);
}

bool BinaryOperation::peekIsBinaryOperator(parserProgress &p){
    return p.peekSymbol(BinaryOperation::binary_symbol_operators)||p.peekKeyword(BinaryOperation::binary_keyword_operators);
}

BinaryOperation::BinaryOperation(int ls,std::shared_ptr<ExpressionTerm> t1,parserProgress &p){
    line_start=ls;
    term1=t1;
    is_keyword=true;
    if(!(binary_keyword_operator=p.isKeyword(binary_keyword_operators))){
        is_keyword=false;
        if(!(binary_operator=p.isSymbol(binary_symbol_operators))){
            throw MyExcept::NoMatchException(p,"binary operator");
        }
    }
    term2=std::make_shared<Expression>(p);
    line_end=p.get_line(-1);
}

BinaryOperation::BinaryOperation(std::shared_ptr<ExpressionTerm> et,std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<Expression> ex,int ls,int le):ParserResultPart(ls,le),term1(et),binary_operator(st),term2(ex),is_keyword(false){
    
}

BinaryOperation::BinaryOperation(std::shared_ptr<ExpressionTerm> et,std::shared_ptr<Lexer::KeywordToken> kt,std::shared_ptr<Expression> ex,int ls,int le):ParserResultPart(ls,le),term1(et),binary_keyword_operator(kt),term2(ex),is_keyword(true){
    
}

std::string BinaryOperation::getSource(){
    return term1->getSource()+(is_keyword?binary_keyword_operator->get_literal():binary_operator->get_literal())+term2->getSource();
}

void BinaryOperation::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"BinaryOperation {\n";
    std::cout<<indent0<<".term1:\n";
    term1->print(depth+1);
    std::cout<<indent0<<".binary_operator:\n"<<indent1<<binary_operator->get_formatted()<<"\n";
    std::cout<<indent0<<".term2:\n";
    term2->print(depth+1);
    std::cout<<indent0<<"}\n";
}
