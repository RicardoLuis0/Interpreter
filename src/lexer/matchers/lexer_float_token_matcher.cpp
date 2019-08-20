#include "lexer_float_token_matcher.h"
#include "lexer_float_token.h"
#include "my_except.h"

static int trymatch(std::string s){
    if(s==".")return 0;
    bool first=true;
    bool decimal=false;
    bool firstzero=false;
    bool last=false;
    for(char c:s){
        if(first){
            if(c<'1'||c>'9'){//must start with either '0-9' or '.'
                if(c=='.'){
                    decimal=true;
                }else if(c=='0'){
                    firstzero=true;
                }else{
                    return 0;
                }
            }
        }else{
            if(firstzero&&c!='.')return 0;
            else firstzero=false;
            if(last)return 0;
            if(c<'0'||c>'9'){
                if(c=='.'){
                    if(decimal) return 0;
                    decimal=true;
                }else if(c=='f'){
                    last=true;
                }else{
                    return 0;
                }
            }
        }
        first=false;
    }
    return (decimal&&s.length()>0)?1:-1;
}

static int ipow(int b,int e){//only works for positives
    int r=1;
    while(e-->0){
        r*=b;
    }
    return r;
}

bool Lexer::FloatTokenMatcher::partialMatch(std::string s){
    return trymatch(s)!=0;
}

bool Lexer::FloatTokenMatcher::fullMatch(std::string s){
    return trymatch(s)==1;
}

std::shared_ptr<Lexer::Token> Lexer::FloatTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        int partial=0;
        bool decimal=false;
        int decimal_t=0;
        for(char c:s){
            if(c=='f')break;
            if(decimal){
                decimal_t++;
            }else{
                if(c=='.'){
                    decimal=true;
                    continue;
                }
            }
            partial*=10;
            partial+=c-'0';
        }
        return std::make_shared<FloatToken>(line,partial/double(ipow(10,decimal_t)));
    }
    throw MyExcept::NoMatchException(line,s);
}
