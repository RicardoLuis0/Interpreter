#include "comment_token_matcher.h"
#include "my_except.h"


bool Lexer::CommentTokenMatcher::partialMatch(std::string s){
    return fullMatch(s);
}

bool Lexer::CommentTokenMatcher::fullMatch(std::string s){
    bool multiline=false;
    bool terminated=false;
    int init=0;
    for(char c:s){
        if(terminated)return false;
        switch(init){
        case 0:
            if(c!='/')return false;
            init++;
            break;
        case 1:
            switch(c){
            case '*':
                multiline=true;
            case '/':
                break;
            default:
                return false;
            }
            init++;
            break;
        case 2:
            switch(c){
            case '\n':
                if(!multiline)terminated=true;
                break;
            case '*':
                if(multiline)init++;
                break;
            default:
                break;
            }
            break;
        case 3:
            if(c=='/'){
                terminated=true;
            }
            init--;
            break;
        }
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::CommentTokenMatcher::makeMatch(int line,std::string s){
    return nullptr;
}
