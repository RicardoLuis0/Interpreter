#ifndef TOKEN_MATCHER_H
#define TOKEN_MATCHER_H

#include <memory>
#include <string>
#include "token.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class TokenMatcher token_matcher.h "token_matcher.h"
     * @brief Abstract base class for Token Matchers ( Main compontents of { @link Lexer } ).
     */

    class TokenMatcher {
        public:
            /**
             * @brief Checks wether a string is a partial match for the {@link Token}
             * 
             * @param input string to check for partial match
             * @return if it is a partial match or not
             */
            virtual bool partialMatch(std::string input)=0;
            /**
             * @brief Checks wether a string is a full match for the {@link Token}
             * 
             * @param input string to check for full match
             * @return if it is a full match or not
             */
            virtual bool fullMatch(std::string input)=0;
            /**
             * @brief Creates a {@link Token} from the input string
             * 
             * May throw {@link MyExcept::NoMatchException} in the case that the input isn't a full match.
             * If the returned pointer is null, it should be ignored.
             * @param line line value to pass to token
             * @param input string to use
             * @return the resulting {@link Token}
             */
            virtual std::shared_ptr<Token> makeMatch(int line,std::string input)=0;
    };

}
#endif // TOKEN_MATCHER_H
