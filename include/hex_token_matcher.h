#ifndef HEX_TOKEN_MATCHER_H
#define HEX_TOKEN_MATCHER_H

#include "integer_token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class HexTokenMatcher hex_token_matcher.h "hex_token_matcher.h"
     * @brief Matches Hexadecimal Integers
     * 
     * regex equivalent /-?0x[0-9A-Fa-f]+/
     */

    class HexTokenMatcher : public IntegerTokenMatcher {
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

#endif // HEX_TOKEN_MATCHER_H
