#include "Parser/ExpressionTerm.h"

#include "symbols_keywords.h"

#include "Lexer/KeywordToken.h"

#include "Parser/ExpressionGroup.h"
#include "Parser/FunctionCall.h"
#include "Parser/KeywordFunctionCall.h"
#include "Parser/UnaryOperation.h"
#include "Parser/VarType.h"

#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

std::vector<int> ExpressionTerm::post_unary_operators{//these must not be binary operators
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
};

ExpressionTerm::ExpressionTerm(parserProgress &p){
    line_start=p.get_line();
    std::shared_ptr<ExpressionTerm> term=nullptr;
    if(p.peekSymbol(SYMBOL_PARENTHESIS_OPEN)){
        contents_p=std::make_shared<ExpressionGroup>(p);
        type=EXPRESSION_TERM_EXPRESSION_GROUP;
    }else if(p.peekType(Lexer::TOKEN_TYPE_WORD)&&p.peekSymbol(SYMBOL_PARENTHESIS_OPEN,1)){
        contents_p=std::make_shared<FunctionCall>(p);
        type=EXPRESSION_TERM_FUNCTION_CALL;
    }else if(p.peekKeyword({KEYWORD_IS,KEYWORD_CAST,KEYWORD_TYPEOF,KEYWORD_TYPE})){
        contents_p=std::make_shared<KeywordFunctionCall>(p);
        type=EXPRESSION_TERM_KEYWORD_FUNCTION_CALL;
    }else if(p.peekType({Lexer::TOKEN_TYPE_KEYWORD,Lexer::TOKEN_TYPE_SYMBOL})){
        int i=p.location;
        try{
            contents_p=std::make_shared<UnaryOperation>(p);//TODO refactor UnaryOperation out, add unary-pre operators to ExpressionTerm
            type=EXPRESSION_TERM_UNARY_OPERATION;
        }catch(MyExcept::NoMatchException &){
            p.location=i;
            contents_p=std::make_shared<VarType>(p);
            type=EXPRESSION_TERM_VARTYPE;
        }
    }else{
        if(contents_t=p.isType(Lexer::TOKEN_TYPE_INTEGER)){//int
            type=EXPRESSION_TERM_LITERAL_INT;
        }else if(contents_t=p.isType(Lexer::TOKEN_TYPE_CHAR)){//float
            type=EXPRESSION_TERM_LITERAL_CHAR;
        }else if(contents_t=p.isType(Lexer::TOKEN_TYPE_FLOAT)){//float
            type=EXPRESSION_TERM_LITERAL_FLOAT;
        }else if(contents_t=p.isType(Lexer::TOKEN_TYPE_STRING)){//string
            type=EXPRESSION_TERM_LITERAL_STRING;
        }else if(contents_t=p.isKeyword({KEYWORD_TRUE,KEYWORD_FALSE,KEYWORD_NULL})){
            switch(std::static_pointer_cast<Lexer::KeywordToken>(contents_t)->get_keyword_type()){
            case KEYWORD_TRUE:
                type=EXPRESSION_TERM_LITERAL_TRUE;
                break;
            case KEYWORD_FALSE:
                type=EXPRESSION_TERM_LITERAL_FALSE;
                break;
            case KEYWORD_NULL:
                type=EXPRESSION_TERM_LITERAL_NULL;
                break;
            default:
                break;//unreachable
            }
        }else if(contents_t=p.isType(Lexer::TOKEN_TYPE_WORD)){//ident
            type=EXPRESSION_TERM_IDENTIFIER;
        } else {
            throw MyExcept::NoMatchException(p,"literal, type, or identifier");
        }
    }
    std::shared_ptr<Lexer::SymbolToken> ptr;
    while(ptr=p.isSymbol(post_unary_operators)){
        unary_post_operators.push_back(ptr);
    }
    while(p.isSymbol(SYMBOL_SQUARE_BRACKET_OPEN)){
        array_access.push_back(std::make_shared<Expression>(p));
        if(!p.isSymbol(SYMBOL_SQUARE_BRACKET_CLOSE)){
            throw MyExcept::NoMatchException(p,"']'");
        }
    }
    if(auto s=p.isSymbol({SYMBOL_DOT,SYMBOL_ARROW})){
        member_access_type=(s->get_symbol_type()==SYMBOL_ARROW)?MEMBER_ACCESS_POINTER:MEMBER_ACCESS_NORMAL;
        member_access=std::make_shared<ExpressionTerm>(p);
    }
    line_end=p.get_line(-1);
}

ExpressionTerm::ExpressionTerm(std::shared_ptr<ParserResultPart> ptr,ExpressionTermType_t ptype,int ls,int le):ParserResultPart(ls,le),contents_p(ptr),contents_t(nullptr),type(ptype){
    
}

ExpressionTerm::ExpressionTerm(std::shared_ptr<Lexer::Token> ptr,ExpressionTermType_t ptype,int ls,int le):ParserResultPart(ls,le),contents_p(nullptr),contents_t(ptr),type(ptype){
    
}

std::string ExpressionTerm::getSource(){
    std::string s;
    if(type>EXPRESSION_TERM_LITERAL){
        s=contents_t->get_literal();
    }else{
        s=contents_p->getSource();
    }
    for(auto op:unary_post_operators){
        s+=op->get_literal();
    }
    for(auto aa:array_access){
        s+="["+aa->getSource()+"]";
    }
    if(member_access_type!=MEMBER_ACCESS_NONE){
        if(member_access_type==MEMBER_ACCESS_NORMAL){
            s+=".";
        }else{
            s+="->";
        }
        s+=member_access->getSource();
    }
    return s;
}

void ExpressionTerm::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::string indent2=get_indent(depth+2);
    std::cout<<indent0<<"ExpressionTerm {\n";
    if(type>EXPRESSION_TERM_LITERAL){
        std::cout<<indent0<<".type:\n"<<indent1<<"EXPRESSION_TERM_LITERAL\n";
        std::cout<<indent0<<".literal:\n"<<indent1<<contents_t->get_formatted()<<"\n";
    }else{
        std::cout<<indent0<<".contents:\n";
        contents_p->print(depth+1);
    }
    if(unary_post_operators.size()>0){
        std::cout<<indent0<<".unary_post_operators:\n";
        for(int i=0;i<int(unary_post_operators.size());i++){
            std::cout<<indent1<<".op["<<i<<"]:\n";
            std::cout<<indent2<<unary_post_operators[i]->get_formatted()<<"\n";
        }
    }
    if(array_access.size()>0){
        std::cout<<indent0<<".array_access:\n";
        for(int i=0;i<int(array_access.size());i++){
            std::cout<<indent1<<".aa["<<i<<"]:\n";
            array_access[i]->print(depth+2);
        }
    }
    if(member_access_type!=MEMBER_ACCESS_NONE){
        std::cout<<indent0<<".member_access_type:\n"<<indent1<<((member_access_type==MEMBER_ACCESS_NORMAL)?"MEMBER_ACCESS_NORMAL":"MEMBER_ACCESS_POINTER")<<"\n"<<indent0<<".member_access:\n";
        member_access->print(depth+1);
    }
    std::cout<<indent0<<"}\n";
}
