#include "integer_token.h"


Lexer::IntegerToken::IntegerToken(int n,int n2):
    Token(n,TOKEN_TYPE_FLOAT),
    d(n2){
}

const std::string Lexer::IntegerToken::get_formatted() const {
    return "[INTEGER] <"+std::to_string(d)+">";
}


const std::string Lexer::IntegerToken::get_literal() const {
    return std::to_string(d);
}

const int Lexer::IntegerToken::get_integer() const {
    return d;
}
