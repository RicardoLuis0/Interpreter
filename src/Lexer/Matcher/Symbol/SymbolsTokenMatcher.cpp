#include "Lexer/SymbolsTokenMatcher.h"
#include "Lexer/SymbolToken.h"
#include "MyExcept/MyExcept.h"

Lexer::SymbolsTokenMatcher::SymbolsTokenMatcher(std::vector<symbol_data> &symbols):symbol_list(symbols){}

bool Lexer::SymbolsTokenMatcher::partialMatch(std::string s){
    for(symbol_data d:symbol_list){
        if(s.length()<=d.str.length()){
            if(d.str.substr(0,s.length())==s) return true;
        }
    }
    return false;
}

bool Lexer::SymbolsTokenMatcher::fullMatch(std::string s){
    for(symbol_data d:symbol_list){
        if(s==d.str)return true;
    }
    return false;
}

std::shared_ptr<Lexer::Token> Lexer::SymbolsTokenMatcher::makeMatch(int line,std::string s){
    if(fullMatch(s)){
        for(symbol_data d:symbol_list){
            if(s==d.str) return std::make_shared<SymbolToken>(line,d);
        }
    }
    throw MyExcept::NoMatchException(line,s);
}

