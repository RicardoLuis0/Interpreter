#ifndef GLOBAL_TOKEN_MATCHER_H
#define GLOBAL_TOKEN_MATCHER_H

#include "Lexer/ListTokenMatcher.h"

#include <vector>

#include "Lexer/keyword_data.h"
#include "Lexer/symbol_data.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer {

    /**
     * @class GlobalTokenMatcher global_token_matcher.h "global_token_matcher.h"
     * @brief Matches all Tokens
     */

    class GlobalTokenMatcher : public ListTokenMatcher {
        public:
            /**
             * @brief Constructor
             * 
             * Initializes List with all Token Matchers
             */
            GlobalTokenMatcher(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords);
    };

}
#endif // GLOBAL_TOKEN_MATCHER_H
