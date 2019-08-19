#include "lexer_char_token.h"

Lexer::CharToken::CharToken(int n,char c2,std::string literal):
    Token(n,TOKEN_TYPE_CHAR),
    c(c2),
    lit(literal){
}

const std::string Lexer::CharToken::get_formatted() const {
    return "[CHAR] <"+std::to_string(c)+">";
}


const std::string Lexer::CharToken::get_literal() const {
    return lit;
}

const char Lexer::CharToken::get_char() const {
    return c;
}
