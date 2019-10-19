#ifndef SINGLE_QUOTE_STRING_TOKEN_MATCHER_H
#define SINGLE_QUOTE_STRING_TOKEN_MATCHER_H

#include "Lexer/StringTokenMatcher.h"

namespace Lexer{

    class CharTokenMatcher : public StringTokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}

#endif // SINGLE_QUOTE_STRING_TOKEN_MATCHER_H
