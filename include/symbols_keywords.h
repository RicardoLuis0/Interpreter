#ifndef SYMBOLS_KEYWORDS_H_INCLUDED
#define SYMBOLS_KEYWORDS_H_INCLUDED

#include "Lexer/keyword_data.h"
#include "Lexer/symbol_data.h"
#include <vector>

enum keyword_type_t{
    KEYWORD_IS,
    KEYWORD_CAST,
    KEYWORD_TYPEOF,
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
    KEYWORD_SIGNED,
    KEYWORD_UNSIGNED,
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_NULL,
    KEYWORD_STATIC,
    KEYWORD_CONST,
    KEYWORD_POINTER,
    KEYWORD_ANY,
    KEYWORD_TYPE,
    KEYWORD_VOID,
    KEYWORD_BOOL,
    KEYWORD_CHAR,
    KEYWORD_INT,
    KEYWORD_FLOAT,
    KEYWORD_STRING,
    KEYWORD_STRUCT,
    KEYWORD_CLASS,
    KEYWORD_PUBLIC,
    KEYWORD_PROTECTED,
    KEYWORD_PRIVATE,
    KEYWORD_OVERRIDE,
    KEYWORD_VIRTUAL,
    _LAST_KEYWORD_,
};

enum symbol_type_t {
    SYMBOL_HASHTAG=_LAST_KEYWORD_,
    SYMBOL_SEMICOLON,
    SYMBOL_COLON,
    SYMBOL_QUESTION_MARK,
    SYMBOL_COMMA,
    SYMBOL_PARENTHESIS_OPEN,
    SYMBOL_PARENTHESIS_CLOSE,
    SYMBOL_SQUARE_BRACKET_OPEN,
    SYMBOL_SQUARE_BRACKET_CLOSE,
    SYMBOL_CURLY_BRACKET_OPEN,
    SYMBOL_CURLY_BRACKET_CLOSE,
    SYMBOL_PLUS,
    SYMBOL_MINUS,
    SYMBOL_MULTIPLY,
    SYMBOL_DIVIDE,
    SYMBOL_PERCENT,
    SYMBOL_INCREMENT,
    SYMBOL_DECREMENT,
    SYMBOL_EQUALS,
    SYMBOL_NOT_EQUALS,
    SYMBOL_GREATER,
    SYMBOL_GREATER_EQUALS,
    SYMBOL_LOWER,
    SYMBOL_LOWER_EQUALS,
    SYMBOL_LOGICAL_AND,
    SYMBOL_LOGICAL_OR,
    SYMBOL_LOGICAL_NOT,
    SYMBOL_BITWISE_AND,
    SYMBOL_BITWISE_OR,
    SYMBOL_BITWISE_XOR,
    SYMBOL_BITWISE_NOT,
    SYMBOL_LEFT_SHIFT,
    SYMBOL_RIGHT_SHIFT,
    SYMBOL_ASSIGNMENT,
    SYMBOL_PLUS_ASSIGNMENT,
    SYMBOL_MINUS_ASSIGNMENT,
    SYMBOL_MULTIPLY_ASSIGNMENT,
    SYMBOL_DIVIDE_ASSIGNMENT,
    SYMBOL_PERCENT_ASSIGNMENT,
    SYMBOL_LEFT_SHIFT_ASSIGNMENT,
    SYMBOL_RIGHT_SHIFT_ASSIGNMENT,
    SYMBOL_BITWISE_AND_ASSIGNMENT,
    SYMBOL_BITWISE_OR_ASSIGNMENT,
    SYMBOL_BITWISE_XOR_ASSIGNMENT,
    SYMBOL_DOT,
    SYMBOL_ARROW,
    SYMBOL_VARIADIC,
};

Lexer::symbol_data get_symbol_data(symbol_type_t);
Lexer::keyword_data get_keyword_data(keyword_type_t);

extern std::vector<Lexer::keyword_data> base_keywords;
extern std::vector<Lexer::symbol_data> base_symbols;

#endif // SYMBOLS_KEYWORDS_H_INCLUDED
