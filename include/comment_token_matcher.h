#ifndef COMMENT_TOKEN_MATCHER_H
#define COMMENT_TOKEN_MATCHER_H

#include "token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class CommentTokenMatcher comment_token_matcher.h "comment_token_matcher.h"
     * @brief Matches and Removes Comments (single and multi line)
     * 
     * regex /(\/\/.*$)|(/\/\*(\n|.)*\*\//)/
     */

    class CommentTokenMatcher : public TokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
                /**
                 * Always returns nullptr.
                 *
                 * @return std::shared_ptr<nullptr>
                 */
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}

#endif // COMMENT_TOKEN_MATCHER_H
