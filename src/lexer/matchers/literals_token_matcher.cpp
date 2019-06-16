#include "literals_token_matcher.h"
#include "integer_token_matcher.h"
#include "float_token_matcher.h"
#include "string_token_matcher.h"
#include "single_quote_string_token_matcher.h"
#include "octal_token_matcher.h"
#include "hex_token_matcher.h"
#include "binary_token_matcher.h"

Lexer::LiteralsTokenMatcher::LiteralsTokenMatcher(){
    list.push_back(std::make_unique<StringTokenMatcher>());
    list.push_back(std::make_unique<SingleQuoteStringTokenMatcher>());
    list.push_back(std::make_unique<OctalTokenMatcher>());
    list.push_back(std::make_unique<HexTokenMatcher>());
    list.push_back(std::make_unique<BinaryTokenMatcher>());
    list.push_back(std::make_unique<IntegerTokenMatcher>());
    list.push_back(std::make_unique<FloatTokenMatcher>());
}
