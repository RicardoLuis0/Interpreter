#ifndef KEYWORD_TOKEN_H
#define KEYWORD_TOKEN_H

#include "Lexer/Token.h"

#include "Lexer/keyword_data.h"

namespace Lexer {
    class KeywordToken : public Token, private keyword_data {
        public:
            KeywordToken(int line,keyword_data data);
            const std::string get_formatted() const override;
            const std::string get_literal() const override;
            const std::string get_name() const;
            const int get_keyword_type() const;
    };

}

#endif // KEYWORD_TOKEN_H
