#include "lexer_token.h"


Lexer::Token::Token(int n,token_type_t t):
    line(n),
    type(t){
}
