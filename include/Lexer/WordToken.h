#ifndef WORD_TOKEN_H
#define WORD_TOKEN_H

#include "Lexer/Token.h"

namespace Lexer{
    class WordToken : public Token {
        public:
            WordToken(int line,const std::string &data);
            const std::string get_literal() const override;
            const std::string get_formatted() const override;
        private:
            const std::string str;
    };

}

#endif // WORD_TOKEN_H
