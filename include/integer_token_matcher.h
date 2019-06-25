#ifndef INTEGER_TOKEN_MATCHER_H
#define INTEGER_TOKEN_MATCHER_H

#include "token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class IntegerTokenMatcher integer_token_matcher.h "integer_token_matcher.h"
     * @brief Matches Decimal Integers
     * 
     * regex /[0-9]+/
     */

    class IntegerTokenMatcher : public TokenMatcher {
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

#endif // INTEGER_TOKEN_MATCHER_H
