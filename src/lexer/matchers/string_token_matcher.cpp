#include "string_token_matcher.h"
#include "string_token.h"
#include "hex_read_util.h"
#include "my_except.h"


bool Lexer::StringTokenMatcher::partialMatch(std::string s){
    bool reading_escape=false;
    bool read_end=false;
    for(size_t i=0;i<s.length();i++){
        if(read_end)return false;
        if(i==0){
            if(s[i]!='"')return false;
        }else if(reading_escape){
            if(s[i]>='0'&&s[i]<='7'){//octal
                if(s[i+1]>='0'&&s[i+1]<='7'){
                    i++;
                    if(s[i+1]>='0'&&s[i+1]<='7'){
                        i++;
                    }
                }
            }else if(s[i]=='h'&&is_hex(s[i+1])&&is_hex(s[i+2])){
                i+=2;
            }
            reading_escape=false;
        }else{
            if(s[i]=='"'){
                read_end=true;
            }else if(s[i]=='\\'){
                reading_escape=true;
            }
        }
    }
    return true;
}

bool Lexer::StringTokenMatcher::fullMatch(std::string s){
    bool reading_escape=false;
    for(size_t i=0;i<s.length();i++){
        if(i==0){
            if(s[i]!='"')return false;
        }else if(reading_escape){
            if(s[i]>='0'&&s[i]<='7'){//octal
                if(s[i+1]>='0'&&s[i+1]<='7'){
                    i++;
                    if(s[i+1]>='0'&&s[i+1]<='7'){
                        i++;
                    }
                }
            }else if(s[i]=='h'&&is_hex(s[i+1])&&is_hex(s[i+2])){
                i+=2;
            }
            reading_escape=false;
        }else{
            if(s[i]=='"'){
                return true;
            }else if(s[i]=='\\'){
                reading_escape=true;
            }
        }
    }
    return false;
}

std::shared_ptr<Lexer::Token> Lexer::StringTokenMatcher::makeMatch(int line,std::string s){
    std::string formatted;
    std::string unformatted;
    bool reading_escape=false;
    for(size_t i=0;i<s.length();i++){
        unformatted+=s[i];
        if(i==0){
            if(s[i]!='"')break;
        }else if(reading_escape){
            switch(s[i]){
            case 'a':
                formatted+='\a';
                break;
            case 'b':
                formatted+='\b';
                break;
            case 'f':
                formatted+='\f';
                break;
            case 'n':
                formatted+='\n';
                break;
            case 'r':
                formatted+='\r';
                break;
            case 't':
                formatted+='\t';
                break;
            case 'v':
                formatted+='\v';
                break;
            case '\\':
                formatted+='\\';
                break;
            case '\'':
                formatted+='\'';
                break;
            case '\"':
                formatted+='\"';
                break;
            case '\?':
                formatted+='\?';
                break;
            default:
                if(s[i]>='0'&&s[i]<='7'){//octal
                    int r=s[i]-'0';
                    if(s[i+1]>='0'&&s[i+1]<='7'){
                        i++;
                        unformatted+=s[i];
                        r*=8;
                        r+=s[i]-'0';
                        if(s[i+1]>='0'&&s[i+1]<='7'){
                            i++;
                            unformatted+=s[i];
                            r*=8;
                            r+=s[i]-'0';
                        }
                    }
                    formatted+=r>255?255:r;
                }else if(s[i]=='h'&&is_hex(s[i+1])&&is_hex(s[i+2])){
                    int hex=get_hex(s[++i])*16;
                    hex+=get_hex(s[++i]);
                    formatted+=hex;
                }else{
                    formatted+=s[i];
                }
            }
            reading_escape=false;
        }else{
            if(s[i]=='"'){
                return std::make_unique<StringToken>(line,formatted,unformatted);
            }else if(s[i]=='\\'){
                reading_escape=true;
            }else{
                formatted+=s[i];
            }
        }
    }
    throw MyExcept::NoMatchException(line,s);
}
