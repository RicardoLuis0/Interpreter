#ifndef SYMBOL_TOKEN_H
#define SYMBOL_TOKEN_H

#include "Lexer/TokenMatcher.h"

#include "Lexer/symbol_data.h"

namespace Lexer{
    class SymbolToken : public Token, private symbol_data {
        public:
            SymbolToken(int line,symbol_data data);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const std::string get_name() const;
            const int get_symbol_type() const;
    };

}
#endif // SYMBOL_TOKEN_H
