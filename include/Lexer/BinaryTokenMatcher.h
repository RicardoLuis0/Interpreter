#ifndef BINARY_TOKEN_MATCHER_H
#define BINARY_TOKEN_MATCHER_H

#include "Lexer/IntegerTokenMatcher.h"

namespace Lexer {
    class BinaryTokenMatcher : public IntegerTokenMatcher {
        public:
            bool partialMatch(std::string s) override;
            bool fullMatch(std::string s) override;
            std::shared_ptr<Token> makeMatch(int line,std::string s) override;
    };

}

#endif // BINARY_TOKEN_MATCHER_H
