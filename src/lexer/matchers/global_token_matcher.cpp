#include "global_token_matcher.h"
#include "symbols_token_matcher.h"
#include "keywords_token_matcher.h"
#include "word_token_matcher.h"
#include "literals_token_matcher.h"
#include "comment_token_matcher.h"


Lexer::GlobalTokenMatcher::GlobalTokenMatcher(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords){
    list.push_back(std::make_shared<SymbolsTokenMatcher>(symbols));
    list.push_back(std::make_shared<LiteralsTokenMatcher>());
    list.push_back(std::make_shared<KeywordsTokenMatcher>(keywords));
    list.push_back(std::make_shared<WordTokenMatcher>());
    list.push_back(std::make_shared<CommentTokenMatcher>());
}
