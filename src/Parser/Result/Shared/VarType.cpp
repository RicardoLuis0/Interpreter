#include "Parser/VarType.h"

#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"

#include <iostream>

using namespace Parser;

VarType::VarType(parserProgress &p){
    throw std::runtime_error("unimplemented");
}

VarType::VarType(std::shared_ptr<Lexer::KeywordToken> tk,bool c,bool h,bool s,std::shared_ptr<VarType> e,int ls,int le):VarType(
    (tk->get_keyword_type()==KEYWORD_POINTER)?PRIMITIVE_POINTER
    :((tk->get_keyword_type()==KEYWORD_ANY)?PRIMITIVE_ANY
    :((tk->get_keyword_type()==KEYWORD_TYPE)?PRIMITIVE_TYPE
    :((tk->get_keyword_type()==KEYWORD_INT)?PRIMITIVE_INT
    :((tk->get_keyword_type()==KEYWORD_CHAR)?PRIMITIVE_CHAR
    :((tk->get_keyword_type()==KEYWORD_FLOAT)?PRIMITIVE_FLOAT
    :((tk->get_keyword_type()==KEYWORD_STRING)?PRIMITIVE_STRING
    :PRIMITIVE_INVALID)))))),c,h,s,e,ls,le){
    if(primitive==PRIMITIVE_INVALID){
        if(tk->get_keyword_type()==KEYWORD_VOID){
            type=VARTYPE_VOID;
        }else{
            throw MyExcept::NoMatchException(tk->line,"expected primitive type, got '"+tk->get_formatted()+"'");
        }
    }
}

VarType::VarType(std::shared_ptr<Expression> de,bool c,int ls,int le):ParserResultPart(ls,le),type(VARTYPE_DECLTYPE),primitive(PRIMITIVE_INVALID),has_sign(false),sign(false),is_const(c),extra(nullptr),decltype_expr(de){
    
}

VarType::VarType(ParserPrimitiveType_t p,bool c,bool h,bool s,std::shared_ptr<VarType> e,int ls,int le):ParserResultPart(ls,le),type(VARTYPE_PRIMITIVE),primitive(p),has_sign(h),sign(s),is_const(c),extra(e),decltype_expr(nullptr){
    
}

std::string VarType::getSource(){
    std::string t=is_const?"const ":"";
    switch(type){
    case VARTYPE_VOID:
        t+="void";
        break;
    case VARTYPE_PRIMITIVE:
        switch(primitive){
        case PRIMITIVE_INVALID:
            throw std::runtime_error("invalid primitive");
        case PRIMITIVE_POINTER:
            t+="ptr<"+extra->getSource()+">";
        case PRIMITIVE_ANY:
            t+="any";
        case PRIMITIVE_TYPE:
            t+="type";
        case PRIMITIVE_INT:
            t+=(has_sign?(sign?"signed int":"unsigned int"):"int");
        case PRIMITIVE_CHAR:
            t+=(has_sign?(sign?"signed char":"unsigned char"):"char");
        case PRIMITIVE_FLOAT:
            t+="float";
        case PRIMITIVE_STRING:
            t+="string";
        }
        break;
    case VARTYPE_IDENTIFIER:
        throw std::runtime_error("unimplemented");
    case VARTYPE_DECLTYPE:
        t+="decltype("+decltype_expr->getSource()+")";
        break;
    }
    for(int i=array_sizes.size()-1;i>0;i--){
        t+="["+array_sizes[i]->getSource()+"]";
    }
    return t;
}

void VarType::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"VarType {\n";
    std::cout<<indent0<<".is_const:\n";
    std::cout<<indent1<<(is_const?"true":"false")<<"\n";
    std::cout<<indent0<<".type:\n";
    if(type==VARTYPE_DECLTYPE){
        std::cout<<indent1<<"decltype\n";
        std::cout<<indent0<<".decltype_expr:\n";
        decltype_expr->print(depth+1);
    }else if(type==VARTYPE_PRIMITIVE&&primitive==PRIMITIVE_POINTER){
        std::cout<<indent1<<"pointer\n";
        std::cout<<indent0<<".pointer_to:\n";
        extra->print(depth+1);
    }else{
        switch(type){
        default:
            throw std::runtime_error("invalid vartype");
        case VARTYPE_VOID:
            std::cout<<indent1<<"void\n";
            break;
        case VARTYPE_PRIMITIVE:
            switch(primitive){
            default:
            case PRIMITIVE_INVALID:
                throw std::runtime_error("invalid primitive");
            case PRIMITIVE_ANY:
                std::cout<<indent1<<"any\n";
                break;
            case PRIMITIVE_TYPE:
                std::cout<<indent1<<"type\n";
                break;
            case PRIMITIVE_INT:
                std::cout<<indent1<<(has_sign?(sign?"signed int\n":"unsigned int\n"):"int\n");
                break;
            case PRIMITIVE_CHAR:
                std::cout<<indent1<<(has_sign?(sign?"signed char\n":"unsigned char\n"):"char\n");
                break;
            case PRIMITIVE_FLOAT:
                std::cout<<indent1<<"float\n";
                break;
            case PRIMITIVE_STRING:
                std::cout<<indent1<<"string\n";
                break;
            }
            break;
        case VARTYPE_IDENTIFIER:
            throw std::runtime_error("unimplemented");
        }
    }
    if(array_sizes.size()>0){
        std::cout<<indent0<<".array_sizes:\n";
        for(int i=array_sizes.size()-1;i>0;i--){
            std::cout<<indent1<<".as["<<((array_sizes.size()-1)-i)<<"]:\n";
            array_sizes[i]->print(depth+2);
        }
    }
    std::cout<<indent0<<"}\n";
}
