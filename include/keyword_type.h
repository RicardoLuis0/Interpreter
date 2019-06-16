#ifndef KEYWORD_TYPE_H_INCLUDED
#define KEYWORD_TYPE_H_INCLUDED


/** @file keyword_type.h */

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @enum keyword_type_t
     * @brief Keyword types 
     */

    enum keyword_type_t{
        KEYWORD_IF,
        KEYWORD_ELSE,
        KEYWORD_SWITCH,
        KEYWORD_CASE,
        KEYWORD_FOR,
        KEYWORD_DO,
        KEYWORD_WHILE,
        KEYWORD_BREAK,
        KEYWORD_CONTINUE,
        KEYWORD_RETURN,
        KEYWORD_UNSIGNED,
        KEYWORD_NULL,
        KEYWORD_TRUE,
        KEYWORD_FALSE,
        KEYWORD_STATIC,
        KEYWORD_VOID,
        KEYWORD_CHAR,
        KEYWORD_INT,
        KEYWORD_FLOAT,
        KEYWORD_STRING,
        KEYWORD_CLASS,
        KEYWORD_PUBLIC,
        KEYWORD_PROTECTED,
        KEYWORD_PRIVATE,
    };

}

#endif // KEYWORD_TYPE_H_INCLUDED
