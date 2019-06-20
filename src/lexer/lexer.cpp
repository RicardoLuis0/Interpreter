#include "lexer.h"
#include "read_file.h"
#include "my_except.h"
#include <iostream>

static bool constexpr is_break(char c){
    return (c==' '||c=='\n'||c=='\t');
}

Lexer::Lexer::Lexer(std::vector<symbol_data> &symbols,std::vector<keyword_data> &keywords):tokenMatcher(symbols,keywords){}

std::vector<std::shared_ptr<Lexer::Token>> Lexer::Lexer::tokenize_from_file(std::string filename){
    std::string str;
    read_file(filename,str);
    return tokenize_from_string(filename,str);
}

std::vector<std::shared_ptr<Lexer::Token>> Lexer::Lexer::tokenize_from_string(std::string filename,std::string &data){
    //GlobalTokenMatcher tokenMatcher(symbols,keywords);
    std::vector<std::shared_ptr<Token>> output;
    std::string buffer;
    int line=1;
    for(char c:data){
        if(c=='\n')line++;
        if(tokenMatcher.partialMatch(buffer+c)){
            buffer+=c;
        }else{
            if(buffer.empty()){
                if(!is_break(c)) throw MyExcept::ParseError(line,"unexpected "+(std::string()=c),filename);
            }else{
                if(tokenMatcher.fullMatch(buffer)){
                    if(auto ptr=tokenMatcher.makeMatch(line,buffer))output.push_back(ptr);
                    is_break(c)?buffer="":buffer=c;
                }else{ throw MyExcept::ParseError(line,"unexpected "+buffer,filename);};
            }
        }
    }
    if(!buffer.empty()){
        if(tokenMatcher.fullMatch(buffer)){
            if(auto ptr=tokenMatcher.makeMatch(line,buffer)){
                output.push_back(ptr);
            }
        }else{ throw MyExcept::ParseError(line,"unexpected "+buffer,filename);};
    }
    return output;
}
