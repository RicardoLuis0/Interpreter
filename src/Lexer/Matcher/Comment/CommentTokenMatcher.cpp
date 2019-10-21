#include "Lexer/CommentTokenMatcher.h"
#include "MyExcept/MyExcept.h"


bool Lexer::CommentTokenMatcher::partialMatch(std::string s){
    return fullMatch(s);
}

bool Lexer::CommentTokenMatcher::fullMatch(std::string s){
    bool multiline=false;
    bool terminated=false;
    bool shebang_start=false;
    int init=0;
    for(char c:s){
        if(terminated)return false;
        switch(init){
        case 0:
            if(c=='#'){
                shebang_start=true;
            }else if(c!='/'){
                return false;
            }
            init++;
            break;
        case 1:
            switch(c){
            case '!':
                if(!shebang_start)return false;
                break;
            case '*':
                multiline=true;
                break;
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
            }else{
                init--;
            }
            break;
        }
    }
    return true;
}

std::shared_ptr<Lexer::Token> Lexer::CommentTokenMatcher::makeMatch(int,std::string){
    return nullptr;
}
