#ifndef STRING_TOKEN_MATCHER_H
#define STRING_TOKEN_MATCHER_H

#include "token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class StringTokenMatcher string_token_matcher.h "string_token_matcher.h"
     * @brief Matches Double Quote Strings (supports escape codes)
     */

    class StringTokenMatcher : public TokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            /**
             * Creates an {@link StringToken} from the input string.
             * 
             * May throw MyExcept::NoMatchException in the case that the input isn't a full match. 
             * @return std::shared_ptr<{@link StringToken}>
             */
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}

#endif // STRING_TOKEN_MATCHER_H
