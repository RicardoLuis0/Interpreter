#ifndef LEXER_CHAR_TOKEN_H
#define LEXER_CHAR_TOKEN_H

#include "lexer_token.h"

namespace Lexer{

    class CharToken : public Token{
        public:
            CharToken(int line,char value,std::string literal);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const char get_char() const;
        private:
            const char c;
            const std::string lit;
    };

}

#endif // LEXER_CHAR_TOKEN_H
