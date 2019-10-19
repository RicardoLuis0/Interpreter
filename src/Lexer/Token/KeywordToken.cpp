#include "Lexer/KeywordToken.h"


Lexer::KeywordToken::KeywordToken(int n,keyword_data d):
    Token(n,TOKEN_TYPE_KEYWORD),
    keyword_data(d){
}

const std::string Lexer::KeywordToken::get_formatted() const {
    return "["+name+"] '"+str+"'";
}

const std::string Lexer::KeywordToken::get_literal() const {
    return str;
}

const std::string Lexer::KeywordToken::get_name() const {
    return name;
}

const int Lexer::KeywordToken::get_keyword_type() const {
    return keyword_data::type;
}
