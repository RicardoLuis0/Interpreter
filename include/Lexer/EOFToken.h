#ifndef EOF_TOKEN_H
#define EOF_TOKEN_H

#include "Lexer/Token.h"


namespace Lexer{
    class EOFToken : public Token{
        public:
            EOFToken(int n);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
    };
}

#endif // EOF_TOKEN_H
