#ifndef INTEGER_TOKEN_H
#define INTEGER_TOKEN_H

#include "Lexer/Token.h"

namespace Lexer{

    class IntegerToken : public Token{
        public:
            IntegerToken(int line,uint32_t value);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const uint32_t get_integer() const;
        private:
            const uint32_t d;
    };

}

#endif // INTEGER_TOKEN_H
