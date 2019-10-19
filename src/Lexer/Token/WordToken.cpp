#include "Lexer/WordToken.h"


Lexer::WordToken::WordToken(int n,const std::string &content):
    Token(n,TOKEN_TYPE_WORD),
    str(content){
}

const std::string Lexer::WordToken::get_literal() const {
    return str;
}

const std::string Lexer::WordToken::get_formatted() const {
    return "[IDENTIFIER] <"+str+">";
}
