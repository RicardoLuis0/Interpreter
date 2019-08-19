#include "lexer_global_token_matcher.h"
#include "lexer_symbols_token_matcher.h"
#include "lexer_keywords_token_matcher.h"
#include "lexer_word_token_matcher.h"
#include "lexer_literals_token_matcher.h"
#include "lexer_comment_token_matcher.h"


Lexer::GlobalTokenMatcher::GlobalTokenMatcher(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords){
    list.push_back(std::make_shared<SymbolsTokenMatcher>(symbols));
    list.push_back(std::make_shared<LiteralsTokenMatcher>());
    list.push_back(std::make_shared<KeywordsTokenMatcher>(keywords));
    list.push_back(std::make_shared<WordTokenMatcher>());
    list.push_back(std::make_shared<CommentTokenMatcher>());
}
