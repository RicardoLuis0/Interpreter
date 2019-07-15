#include "list_token_matcher.h"
#include "my_except.h"


bool Lexer::ListTokenMatcher::partialMatch(std::string s){
    for(std::shared_ptr<TokenMatcher>& m:list){
        if(m->partialMatch(s))return true;
    }
    return false;
}

bool Lexer::ListTokenMatcher::fullMatch(std::string s){
    for(std::shared_ptr<TokenMatcher>& m:list){
        if(m->fullMatch(s))return true;
    }
    return false;
}

std::shared_ptr<Lexer::Token> Lexer::ListTokenMatcher::makeMatch(int line,std::string s){
    for(std::shared_ptr<TokenMatcher>& m:list){
        if(m->fullMatch(s)) return m->makeMatch(line,s);
    }
    throw MyExcept::NoMatchException(line,s);
}

Lexer::ListTokenMatcher::~ListTokenMatcher(){}
