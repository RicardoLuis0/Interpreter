#include "Lexer/SymbolToken.h"


Lexer::SymbolToken::SymbolToken(int n,symbol_data d):
    Token(n,TOKEN_TYPE_SYMBOL),
    symbol_data(d){
}

const std::string Lexer::SymbolToken::get_formatted() const {
    return "["+name+"] '"+str+"'";
}

const std::string Lexer::SymbolToken::get_literal() const {
    return str;
}

const std::string Lexer::SymbolToken::get_name() const {
    return name;
}

const int Lexer::SymbolToken::get_symbol_type() const {
    return symbol_data::type;
}
