#ifndef GLOBAL_TOKEN_MATCHER_H
#define GLOBAL_TOKEN_MATCHER_H

#include "Lexer/ListTokenMatcher.h"

#include <vector>

#include "Lexer/keyword_data.h"
#include "Lexer/symbol_data.h"

namespace Lexer {
    class GlobalTokenMatcher : public ListTokenMatcher {
        public:
            GlobalTokenMatcher(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords);
    };

}
#endif // GLOBAL_TOKEN_MATCHER_H
