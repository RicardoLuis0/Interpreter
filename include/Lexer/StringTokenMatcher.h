#ifndef STRING_TOKEN_MATCHER_H
#define STRING_TOKEN_MATCHER_H

#include "Lexer/TokenMatcher.h"
#include "Lexer/StringToken.h"

namespace Lexer{
    class StringTokenMatcher : public TokenMatcher {
    protected:
            bool partialMatchString(std::string s,char c);
            bool fullMatchString(std::string s,char c);
            std::shared_ptr<StringToken> matchString(int line,std::string s,char c);
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}

#endif // STRING_TOKEN_MATCHER_H
