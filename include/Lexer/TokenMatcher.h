#ifndef TOKEN_MATCHER_H
#define TOKEN_MATCHER_H

#include <memory>
#include <string>
#include "Lexer/Token.h"

namespace Lexer{
    class TokenMatcher {
        public:
            virtual bool partialMatch(std::string input)=0;
            virtual bool fullMatch(std::string input)=0;
            virtual std::shared_ptr<Token> makeMatch(int line,std::string input)=0;
    };

}
#endif // TOKEN_MATCHER_H
