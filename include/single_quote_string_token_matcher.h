#ifndef SINGLE_QUOTE_STRING_TOKEN_MATCHER_H
#define SINGLE_QUOTE_STRING_TOKEN_MATCHER_H

#include "string_token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class SingleQuoteStringTokenMatcher single_quote_string_token_matcher.h "single_quote_string_token_matcher.h"
     * @brief Matches Single Quote Strings (supports escape codes)
     */

    class SingleQuoteStringTokenMatcher : public StringTokenMatcher {
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

#endif // SINGLE_QUOTE_STRING_TOKEN_MATCHER_H
