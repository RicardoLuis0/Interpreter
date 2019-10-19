#include "Lexer/WordTokenMatcher.h"
#include "Lexer/WordToken.h"
#include "MyExcept/MyExcept.h"


bool Lexer::WordTokenMatcher::partialMatch(std::string s){
    return fullMatch(s);
}

bool Lexer::WordTokenMatcher::fullMatch(std::string s){
    if(s.empty())return false;
    if(s[0]>='0'&&s[0]<='9')return false;
    for(char c:s){
        if(!((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')||c=='_')){
            return false;
        }
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::WordTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        return std::make_shared<WordToken>(line,s);
    }
    throw MyExcept::NoMatchException(line,s);
}
