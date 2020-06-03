#ifndef LITERALS_TOKEN_MATCHER_H
#define LITERALS_TOKEN_MATCHER_H

#include "Lexer/ListTokenMatcher.h"

namespace Lexer{
    class LiteralsTokenMatcher : public ListTokenMatcher {
        public:
            LiteralsTokenMatcher();
    };
}
#endif // LITERALS_TOKEN_MATCHER_H
