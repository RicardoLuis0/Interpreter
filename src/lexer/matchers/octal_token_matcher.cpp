#include "octal_token_matcher.h"
#include "integer_token.h"
#include "my_except.h"


bool Lexer::OctalTokenMatcher::partialMatch(std::string s){
    return fullMatch(s);
}

bool Lexer::OctalTokenMatcher::fullMatch(std::string s){
    bool first=true;
    bool second=true;
    bool negative=false;
    for(char c:s){
        if(first){
            first=false;
            if(c!='0'){
                if(c=='-')negative=true;
                else return false;
            }
        }else if(second){
            second=false;
            if(negative){
                if(c!='0')return false;
            }else{
                if(!(c>='0'&&c<='7'))return false;
            }
        }else{
            if(!(c>='0'&&c<='7'))return false;
        }
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::OctalTokenMatcher::makeMatch(int line,std::string s){
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
            d*=8;
            d+=c-'0';
        }
        return std::make_unique<IntegerToken>(line,negative?-d:d);
    }
    throw MyExcept::NoMatchException(line,s);
}
