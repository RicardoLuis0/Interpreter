#ifndef WORD_TOKEN_MATCHER_H
#define WORD_TOKEN_MATCHER_H

#include "lexer_token_matcher.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class WordTokenMatcher word_token_matcher.h "word_token_matcher.h"
     * @brief Matches Words
     * 
     * regex equivalent /[a-zA-Z_][a-zA-Z0-9_]* /
     */

    class WordTokenMatcher : public TokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            /**
             * Creates an {@link WordToken} from the input string.
             * 
             * May throw MyExcept::NoMatchException in the case that the input isn't a full match. 
             * @return std::shared_ptr<{@link WordToken}>
             */
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}
#endif // WORD_TOKEN_MATCHER_H
