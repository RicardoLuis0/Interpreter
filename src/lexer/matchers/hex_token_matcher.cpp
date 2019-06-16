#include "hex_token_matcher.h"
#include "hex_read_util.h"
#include "integer_token.h"
#include "my_except.h"


bool Lexer::HexTokenMatcher::partialMatch(std::string s){
    return fullMatch(s);
}

bool Lexer::HexTokenMatcher::fullMatch(std::string s){
    bool first=true;
    bool second=true;
    bool third=true;
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
                if(c!='x')return false;
            }
        }else if(third){
            third=false;
            if(negative){
                if(c!='x')return false;
            }else if(!is_hex(c))return false;
        }else{
            if(!is_hex(c))return false;
        }
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::HexTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        int d=0;
        bool first=true,second=true,third=true,negative=false;
        for(char c:s){
            if(first){
                first=false;
                if(c=='-'){
                    negative=true;
                }
                continue;
            }else if(second){
                second=false;
                continue;
            }else if(third){
                third=false;
                if(negative)continue;
            }
            d*=16;
            d+=get_hex(c);
        }
        return std::make_unique<IntegerToken>(line,negative?-d:d);
    }
    throw MyExcept::NoMatchException(line,s);
}
