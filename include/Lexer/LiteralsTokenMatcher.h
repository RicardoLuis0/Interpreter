#ifndef LITERALS_TOKEN_MATCHER_H
#define LITERALS_TOKEN_MATCHER_H

#include "Lexer/ListTokenMatcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class LiteralsTokenMatcher literals_token_matcher.h "literals_token_matcher.h"
     * @brief Matches all Literals
     *
     * Literals:
     *  {@link FloatTokenMatcher}
     *  {@link HexTokenMatcher}
     *  {@link IntegerTokenMatcher}
     *  {@link OctalTokenMatcher}
     *  {@link BinaryTokenMatcher}
     *  {@link StringTokenMatcher}
     *  {@link SingleQuoteStringTokenMatcher}
     */

    class LiteralsTokenMatcher : public ListTokenMatcher {
        public:
            /**
             * @brief Constructor
             * 
             * Initializes List with Literals Token Matchers
             */
            LiteralsTokenMatcher();
    };
}
#endif // LITERALS_TOKEN_MATCHER_H
