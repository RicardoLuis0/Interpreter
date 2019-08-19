#include "lexer_literals_token_matcher.h"
#include "lexer_integer_token_matcher.h"
#include "lexer_float_token_matcher.h"
#include "lexer_string_token_matcher.h"
#include "lexer_single_quote_string_token_matcher.h"
#include "lexer_octal_token_matcher.h"
#include "lexer_hex_token_matcher.h"
#include "lexer_binary_token_matcher.h"

Lexer::LiteralsTokenMatcher::LiteralsTokenMatcher(){
    list.push_back(std::make_shared<StringTokenMatcher>());
    list.push_back(std::make_shared<SingleQuoteStringTokenMatcher>());
    list.push_back(std::make_shared<OctalTokenMatcher>());
    list.push_back(std::make_shared<HexTokenMatcher>());
    list.push_back(std::make_shared<BinaryTokenMatcher>());
    list.push_back(std::make_shared<IntegerTokenMatcher>());
    list.push_back(std::make_shared<FloatTokenMatcher>());
}
