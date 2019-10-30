#include "Parser/ExpressionTerm.h"

#include <iostream>

using namespace Parser;

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
