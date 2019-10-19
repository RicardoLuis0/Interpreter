#include "Lexer/OctalTokenMatcher.h"
#include "Lexer/IntegerToken.h"
#include "MyExcept/MyExcept.h"


bool Lexer::OctalTokenMatcher::partialMatch(std::string s){
    if(s.size()==1&&s=="0")return true;
    return fullMatch(s);
}

bool Lexer::OctalTokenMatcher::fullMatch(std::string s){
    bool first=true;
    bool second=true;
    for(char c:s){
        if(first){
            first=false;
            if(c!='0'){
                return false;
            }
        }else if(second){
            second=false;
            if(c!='o')return false;
        }else{
            if(!(c>='0'&&c<='7'))return false;
        }
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::OctalTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        int d=0;
        bool first=true,second=true;
        for(char c:s){
            if(first){
                first=false;
                continue;
            }
            if(second){
                second=false;
                continue;
            }
            d*=8;
            d+=c-'0';
        }
        return std::make_shared<IntegerToken>(line,d);
    }
    throw MyExcept::NoMatchException(line,s);
}
