#include "Lexer/IntegerTokenMatcher.h"
#include "Lexer/IntegerToken.h"
#include "MyExcept/MyExcept.h"


bool Lexer::IntegerTokenMatcher::partialMatch(std::string s){
    return fullMatch(s);
}

bool Lexer::IntegerTokenMatcher::fullMatch(std::string s){
    for(char c:s){
        if(c<'0'||c>'9')return false;
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::IntegerTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        int d=0;
        bool first=true;
        for(char c:s){
            if(first){
                first=false;
            }
            d*=10;
            d+=c-'0';
        }
        return std::make_shared<IntegerToken>(line,d);
    }
    throw MyExcept::NoMatchException(line,s);
}
