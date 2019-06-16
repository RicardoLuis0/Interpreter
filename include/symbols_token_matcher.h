#ifndef SYMBOLS_TOKEN_MATCHER_H
#define SYMBOLS_TOKEN_MATCHER_H

#include <vector>

#include "token_matcher.h"
#include "symbol_data.h"

/**
 * @namespace Lexer
 * @brief Main Namespace for Lexer
 */
namespace Lexer{

    /**
     * @class SymbolsTokenMatcher symbols_token_matcher.h "symbols_token_matcher.h"
     * @brief Matches Symbols ( {@link #Lexer::symbol_type_t} )
     */

    class SymbolsTokenMatcher : public TokenMatcher {
        public:
            SymbolsTokenMatcher(std::vector<symbol_data> &symbols);
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            /**
             * Creates an {@link SymbolToken} from the input string.
             * 
             * May throw MyExcept::NoMatchException in the case that the input isn't a full match. 
             * @return std::shared_ptr<{@link SymbolToken}>
             */
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
        protected:
            const std::vector<symbol_data> symbol_list;
    };

}
#endif // SYMBOLS_TOKEN_MATCHER_H
