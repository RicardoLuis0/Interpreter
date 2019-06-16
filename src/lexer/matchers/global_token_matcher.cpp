#include "global_token_matcher.h"
#include "symbols_token_matcher.h"
#include "keywords_token_matcher.h"
#include "word_token_matcher.h"
#include "literals_token_matcher.h"
#include "comment_token_matcher.h"


Lexer::GlobalTokenMatcher::GlobalTokenMatcher(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords){
    list.push_back(std::make_unique<LiteralsTokenMatcher>());
    list.push_back(std::make_unique<KeywordsTokenMatcher>(keywords));
    list.push_back(std::make_unique<WordTokenMatcher>());
    list.push_back(std::make_unique<SymbolsTokenMatcher>(symbols));
    list.push_back(std::make_unique<CommentTokenMatcher>());
}
