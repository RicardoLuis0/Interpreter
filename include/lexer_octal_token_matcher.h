#ifndef OCTAL_TOKEN_MATCHER_H
#define OCTAL_TOKEN_MATCHER_H

#include "lexer_integer_token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class OctalTokenMatcher octal_token_matcher.h "octal_token_matcher.h"
     * @brief Matches Octal Integers
     * 
     * regex /0o[0-7]* /
     */

    class OctalTokenMatcher : public IntegerTokenMatcher {
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

#endif // OCTAL_TOKEN_MATCHER_H
