#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

namespace Lexer{
    enum token_type_t {
        TOKEN_TYPE_INVALID,
        TOKEN_TYPE_KEYWORD,
        TOKEN_TYPE_SYMBOL,
        TOKEN_TYPE_WORD,
        TOKEN_TYPE_STRING,
        TOKEN_TYPE_INTEGER,
        TOKEN_TYPE_CHAR,
        TOKEN_TYPE_FLOAT,
    };
}

#endif // TOKEN_TYPE_H
