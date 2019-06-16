#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

/** @file token_type.h */

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @enum token_type_t
     * @brief Token types
     */
    enum token_type_t {
        TOKEN_TYPE_INVALID,
        TOKEN_TYPE_KEYWORD,
        TOKEN_TYPE_SYMBOL,
        TOKEN_TYPE_WORD,
        TOKEN_TYPE_STRING,
        TOKEN_TYPE_INTEGER,
        TOKEN_TYPE_FLOAT,
    };

}

#endif // TOKEN_TYPE_H
