#include "parser_var_type.h"

#include "symbols_keywords.h"
#include "my_except.h"

using namespace Parser;

VarType::VarType(std::shared_ptr<Lexer::KeywordToken> tk,bool c,bool h,bool s,std::shared_ptr<VarType> extra,int ls,int le):VarType(
    (tk->get_keyword_type()==KEYWORD_POINTER)?PRIMITIVE_POINTER
    :((tk->get_keyword_type()==KEYWORD_ANY)?PRIMITIVE_ANY
    :((tk->get_keyword_type()==KEYWORD_TYPE)?PRIMITIVE_TYPE
    :((tk->get_keyword_type()==KEYWORD_INT)?PRIMITIVE_INT
    :((tk->get_keyword_type()==KEYWORD_CHAR)?PRIMITIVE_CHAR
    :((tk->get_keyword_type()==KEYWORD_FLOAT)?PRIMITIVE_FLOAT
    :((tk->get_keyword_type()==KEYWORD_STRING)?PRIMITIVE_STRING
    :PRIMITIVE_INVALID)))))),c,h,s,extra,ls,le){
    if(primitive==PRIMITIVE_INVALID){
        if(tk->get_keyword_type()==KEYWORD_VOID){
            type=VARTYPE_VOID;
        }else{
            throw MyExcept::NoMatchException(tk->line,"expected primitive type, got '"+tk->get_formatted()+"'");
        }
    }
}

VarType::VarType(ParserPrimitiveType_t p,bool c,bool h,bool s,std::shared_ptr<VarType> e,int ls,int le):ParserResultPart(ls,le),primitive(p),type(VARTYPE_PRIMITIVE),has_sign(h),sign(s),is_const(c),extra(e){
}
