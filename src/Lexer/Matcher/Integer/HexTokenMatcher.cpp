#include "lexer_hex_token_matcher.h"
#include "hex_read_util.h"
#include "lexer_integer_token.h"
#include "my_except.h"


bool Lexer::HexTokenMatcher::partialMatch(std::string s){
    if(s.size()==1&&s=="0")return true;
    return fullMatch(s);
}

bool Lexer::HexTokenMatcher::fullMatch(std::string s){
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
            if(c!='x')return false;
        }else{
            if(!is_hex(c))return false;
        }
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::HexTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        int d=0;
        bool first=true,second=true;
        for(char c:s){
            if(first){
                first=false;
                continue;
            }else if(second){
                second=false;
                continue;
            }
            d*=16;
            d+=get_hex(c);
        }
        return std::make_shared<IntegerToken>(line,d);
    }
    throw MyExcept::NoMatchException(line,s);
}