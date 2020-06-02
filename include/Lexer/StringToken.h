#ifndef STRING_TOKEN_H
#define STRING_TOKEN_H

#include "Lexer/Token.h"

namespace Lexer{
    class StringToken : public Token{
        public:
            StringToken(int line,const std::string &processed_string,const std::string &raw_string);
            const std::string get_string() const;
            const std::string get_literal() const override;
            const std::string get_formatted() const override;
        private:
            const std::string processed_string,raw_string;
    };

}
#endif // STRING_TOKEN_H
