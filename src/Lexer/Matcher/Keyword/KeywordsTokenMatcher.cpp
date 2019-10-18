#include "lexer_keywords_token_matcher.h"
#include "lexer_keyword_token.h"
#include "my_except.h"

Lexer::KeywordsTokenMatcher::KeywordsTokenMatcher(std::vector<keyword_data> &keywords):keyword_list(keywords){}

bool Lexer::KeywordsTokenMatcher::partialMatch(std::string s){
    for(keyword_data d:keyword_list){
        if(s.length()<=d.str.length()){
            if(d.str.substr(0,s.length())==s) return true;
        }
    }
    return false;
}
bool Lexer::KeywordsTokenMatcher::fullMatch(std::string s){
    for(keyword_data d:keyword_list){
        if(s==d.str)return true;
    }
    return false;
}
std::shared_ptr<Lexer::Token> Lexer::KeywordsTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        for(keyword_data d:keyword_list){
            if(s==d.str) return std::make_shared<KeywordToken>(line,d);
        }
    }
    throw MyExcept::NoMatchException(line,s);
}
