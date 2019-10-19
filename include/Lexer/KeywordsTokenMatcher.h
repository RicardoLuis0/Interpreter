#ifndef KEYWORDS_TOKEN_MATCHER_H
#define KEYWORDS_TOKEN_MATCHER_H

#include <vector>

#include "Lexer/TokenMatcher.h"
#include "Lexer/keyword_data.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class KeywordsTokenMatcher keywords_token_matcher.h "keywords_token_matcher.h"
     * @brief Matches Keywords ( {@link #Lexer::keyword_type_t} )
     */

    class KeywordsTokenMatcher : public TokenMatcher {
        public:
            KeywordsTokenMatcher(std::vector<keyword_data> &keywords);
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            /**
             * Creates an {@link KeywordToken} from the input string.
             * 
             * May throw MyExcept::NoMatchException in the case that the input isn't a full match. 
             * @return std::shared_ptr<{@link KeywordToken}>
             */
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
        protected:
            const std::vector<keyword_data> keyword_list;
    };

}

#endif // KEYWORDS_TOKEN_MATCHER_H
