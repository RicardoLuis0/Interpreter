#include "parser_var_type_matcher.h"

#include "keyword_token.h"
#include "symbols_keywords.h"
#include "my_except.h"

//VarType = keyword 'void' | keyword 'int' | keyword 'float' | keyword 'string' ;

std::shared_ptr<Parser::VarType> Parser::VarTypeMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<Lexer::KeywordToken> kw=p.isKeyword({KEYWORD_VOID,KEYWORD_INT,KEYWORD_FLOAT,KEYWORD_STRING});
    if(kw){
        return std::make_shared<VarType>(kw);
    }else{
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected variable type, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    }
}
