#ifndef KEYWORDS_TOKEN_MATCHER_H
#define KEYWORDS_TOKEN_MATCHER_H

#include <vector>

#include "Lexer/TokenMatcher.h"
#include "Lexer/keyword_data.h"

namespace Lexer{
    class KeywordsTokenMatcher : public TokenMatcher {
        public:
            KeywordsTokenMatcher(std::vector<keyword_data> &keywords);
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
        protected:
            const std::vector<keyword_data> keyword_list;
    };

}

#endif // KEYWORDS_TOKEN_MATCHER_H
