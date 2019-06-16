#ifndef FLOAT_TOKEN_MATCHER_H
#define FLOAT_TOKEN_MATCHER_H

#include "token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @class FloatTokenMatcher float_token_matcher.h "float_token_matcher.h"
     * @brief Matches Floating Point Numbers ( Dobule precision )
     */

    class FloatTokenMatcher : public TokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            /**
             * Creates an {@link FloatToken} from the input string.
             * 
             * May throw MyExcept::NoMatchException in the case that the input isn't a full match. 
             * @return std::shared_ptr<{@link FloatToken}>
             */
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}

#endif // FLOAT_TOKEN_MATCHER_H
