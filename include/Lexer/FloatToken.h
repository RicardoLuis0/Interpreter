#ifndef FLOAT_TOKEN_H
#define FLOAT_TOKEN_H

#include "Lexer/Token.h"


namespace Lexer {
    class FloatToken : public Token {
        public:
            FloatToken(int line,double value);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const double get_float() const;
        private:
            const double f;
    };

}

#endif // FLOAT_TOKEN_H
