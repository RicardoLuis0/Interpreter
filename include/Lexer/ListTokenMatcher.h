#ifndef LIST_TOKEN_MATCHER_H
#define LIST_TOKEN_MATCHER_H

#include <vector>
#include "Lexer/TokenMatcher.h"

namespace Lexer {
    class ListTokenMatcher : public TokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
        protected:
            std::vector<std::shared_ptr<TokenMatcher>> list;
            virtual ~ListTokenMatcher()=0;
    };

}
#endif // LIST_TOKEN_MATCHER_H
