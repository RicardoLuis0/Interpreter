#include "parser_var_type.h"

#include "symbols_keywords.h"
#include "my_except.h"

Parser::VarType::VarType(std::shared_ptr<Lexer::KeywordToken> tk):VarType(
    (tk->get_keyword_type()==KEYWORD_INT)?PRIMITIVE_INT
    :((tk->get_keyword_type()==KEYWORD_FLOAT)?PRIMITIVE_FLOAT
    :((tk->get_keyword_type()==KEYWORD_STRING)?PRIMITIVE_STRING
    :PRIMITIVE_INVALID))){
    if(primitive==PRIMITIVE_INVALID){
        if(tk->get_keyword_type()==KEYWORD_VOID){
            type=VARTYPE_VOID;
        }else{
            throw MyExcept::NoMatchException(tk->line,"expected primitive type, got '"+tk->get_formatted()+"'");
        }
    }
}

Parser::VarType::VarType(ParserPrimitiveType_t p):primitive(p),type(VARTYPE_PRIMITIVE){
}

Parser::VarType::VarType(ParserVarTypeType_t vt):primitive(PRIMITIVE_INVALID),type(vt){
}
