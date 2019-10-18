#include "lexer_string_token.h"

Lexer::StringToken::StringToken(int n,const std::string &str01,const std::string &str02):
    Token(n,TOKEN_TYPE_STRING),
    processed_string(str01),
    raw_string(str02){
}

const std::string Lexer::StringToken::get_string() const {
    return processed_string;
}

const std::string Lexer::StringToken::get_literal() const {
    return raw_string;
}

const std::string Lexer::StringToken::get_formatted() const {
    return "[STRING] <"+raw_string+">";
}
