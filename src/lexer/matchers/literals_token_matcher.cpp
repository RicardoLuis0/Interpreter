#include "literals_token_matcher.h"
#include "integer_token_matcher.h"
#include "float_token_matcher.h"
#include "string_token_matcher.h"
#include "single_quote_string_token_matcher.h"
#include "octal_token_matcher.h"
#include "hex_token_matcher.h"
#include "binary_token_matcher.h"

Lexer::LiteralsTokenMatcher::LiteralsTokenMatcher(){
    list.push_back(std::make_shared<StringTokenMatcher>());
    list.push_back(std::make_shared<SingleQuoteStringTokenMatcher>());
    list.push_back(std::make_shared<OctalTokenMatcher>());
    list.push_back(std::make_shared<HexTokenMatcher>());
    list.push_back(std::make_shared<BinaryTokenMatcher>());
    list.push_back(std::make_shared<IntegerTokenMatcher>());
    list.push_back(std::make_shared<FloatTokenMatcher>());
}
