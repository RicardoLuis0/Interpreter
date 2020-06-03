#ifndef WORD_TOKEN_MATCHER_H
#define WORD_TOKEN_MATCHER_H

#include "Lexer/TokenMatcher.h"

namespace Lexer{
    class WordTokenMatcher : public TokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}
#endif // WORD_TOKEN_MATCHER_H
