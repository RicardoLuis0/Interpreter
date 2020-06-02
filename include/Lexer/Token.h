#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include "Lexer/token_type.h"

namespace Lexer{
    class Token {
        public:
            const int line;
            const token_type_t type;
            Token(int line,token_type_t type);
            virtual const std::string get_literal() const =0;
            virtual const std::string get_formatted() const =0;
    };

}
#endif // TOKEN_H
