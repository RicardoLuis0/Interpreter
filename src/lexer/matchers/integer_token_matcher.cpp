#include "integer_token_matcher.h"
#include "integer_token.h"
#include "my_except.h"


bool Lexer::IntegerTokenMatcher::partialMatch(std::string s){
    return fullMatch(s);
}

bool Lexer::IntegerTokenMatcher::fullMatch(std::string s){
    bool first;
    for(char c:s){
        if(first?!((c>='0'&&c<='9')||c=='-'):!(c>='0'&&c<='9'))return false;
        first=false;
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::IntegerTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        int d=0;
        bool first=true,negative=false;
        for(char c:s){
            if(first){
                first=false;
                if(c=='-'){
                    negative=true;
                    continue;
                }
            }
            d*=10;
            d+=c-'0';
        }
        return std::make_unique<IntegerToken>(line,negative?-d:d);
    }
    throw MyExcept::NoMatchException(line,s);
}
