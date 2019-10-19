#include "Lexer/GlobalTokenMatcher.h"
#include "Lexer/SymbolsTokenMatcher.h"
#include "Lexer/KeywordsTokenMatcher.h"
#include "Lexer/WordTokenMatcher.h"
#include "Lexer/LiteralsTokenMatcher.h"
#include "Lexer/CommentTokenMatcher.h"


Lexer::GlobalTokenMatcher::GlobalTokenMatcher(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords){
    list.push_back(std::make_shared<SymbolsTokenMatcher>(symbols));
    list.push_back(std::make_shared<LiteralsTokenMatcher>());
    list.push_back(std::make_shared<KeywordsTokenMatcher>(keywords));
    list.push_back(std::make_shared<WordTokenMatcher>());
    list.push_back(std::make_shared<CommentTokenMatcher>());
}
