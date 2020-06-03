#ifndef SYMBOLS_TOKEN_MATCHER_H
#define SYMBOLS_TOKEN_MATCHER_H

#include <vector>

#include "Lexer/TokenMatcher.h"
#include "Lexer/symbol_data.h"

namespace Lexer{
    class SymbolsTokenMatcher : public TokenMatcher {
        public:
            SymbolsTokenMatcher(std::vector<symbol_data> &symbols);
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
        protected:
            const std::vector<symbol_data> symbol_list;
    };

}
#endif // SYMBOLS_TOKEN_MATCHER_H
