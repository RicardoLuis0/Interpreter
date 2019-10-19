#include "Lexer/EOFToken.h"


Lexer::EOFToken::EOFToken(int n):
    Token(n,TOKEN_TYPE_INVALID){
}

const std::string Lexer::EOFToken::get_formatted() const {
    return "[EOF]";
}


const std::string Lexer::EOFToken::get_literal() const {
    return "EOF";
}
