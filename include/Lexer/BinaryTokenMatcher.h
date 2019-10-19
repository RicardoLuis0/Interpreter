#ifndef BINARY_TOKEN_MATCHER_H
#define BINARY_TOKEN_MATCHER_H

#include "Lexer/IntegerTokenMatcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @class BinaryTokenMatcher binary_token_matcher.h "binary_token_matcher.h"
     * @brief Matches Binary Integers
     * 
     * regex / 0b[01]* /
     */

    class BinaryTokenMatcher : public IntegerTokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            /**
             * Creates an {@link IntegerToken} from the input string.
             * 
             * May throw MyExcept::NoMatchException in the case that the input isn't a full match. 
             * @return std::shared_ptr<{@link IntegerToken}>
             */
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}

#endif // BINARY_TOKEN_MATCHER_H
