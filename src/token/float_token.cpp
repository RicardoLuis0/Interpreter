#include "float_token.h"


Lexer::FloatToken::FloatToken(int n,double f):
    Token(n,TOKEN_TYPE_FLOAT),
    f(f){
}

const std::string Lexer::FloatToken::get_formatted() const {
    return "[FLOAT] <"+std::to_string(f)+">";
}

const std::string Lexer::FloatToken::get_literal() const {
    return std::to_string(f);
}

const double Lexer::FloatToken::get_float() const {
    return f;
}
