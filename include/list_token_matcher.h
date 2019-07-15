#ifndef LIST_TOKEN_MATCHER_H
#define LIST_TOKEN_MATCHER_H

#include <vector>
#include "token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @class ListTokenMatcher list_token_matcher.h "list_token_matcher.h"
     * @brief Abstrasct, Matches all TokenMatchers in internal List
     */

    class ListTokenMatcher : public TokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
        protected:
            std::vector<std::shared_ptr<TokenMatcher>> list;/**< @brief TokenMatchers to match */
            virtual ~ListTokenMatcher()=0;/**< @brief Pure virtual destructor */
    };

}
#endif // LIST_TOKEN_MATCHER_H
