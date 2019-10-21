#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <string>
#include <vector>
#include "Lexer/Token.h"
#include "Lexer/SymbolToken.h"
#include "Lexer/KeywordToken.h"

namespace Parser{
    struct parserProgress{
		parserProgress(const std::vector<std::shared_ptr<Lexer::Token>> &data, int location=0);
        bool in_range(int offset=0);
        bool peekType(Lexer::token_type_t id,int offset=0);//check if token is of type, don't change location
        bool peekSymbol(int id,int offset=0);//check if current token is a specific symbol, don't change location
        bool peekSymbol(std::vector<int> ids,int offset=0);//check if current token is one of the symbol inside vector, don't change location
        bool peekKeyword(int id,int offset=0);//check if current token is a specific keyword, don't change location
        bool peekKeyword(std::vector<int> ids,int offset=0);//check if current token is one of the keywords inside vector, don't change location
        std::shared_ptr<Lexer::Token> isType(Lexer::token_type_t id);//check if token is of type, if yes advance location by 1 and return pointer, if not return nullptr
        bool isSymbol(int id);//check if current token is a specific symbol, if yes advances location by 1
        std::shared_ptr<Lexer::SymbolToken> isSymbol(std::vector<int> ids);//check if current token is one of the symbols inside vector, if yes advances location by 1
        bool isKeyword(int id);//check if current token is a specific keyword, if yes advances location by 1
        std::shared_ptr<Lexer::KeywordToken> isKeyword(std::vector<int> ids);//check if current token is one of the keywords inside vector, if yes advances location by 1{
        int get_line(int offset=0);//get line in index+offset,if invalid return either 0 or last line number
        std::shared_ptr<Lexer::Token> get(int offset=0);//get index+offset,if not available throws
        std::shared_ptr<Lexer::Token> get_nothrow(int offset=0);//if not available, returns null
        std::shared_ptr<Lexer::Token> get_nothrow_nonull(int offset=0);//if not available, returns a dummy token "EOF"
        const std::vector<std::shared_ptr<Lexer::Token>> &data;
        int location;
        parserProgress& operator--();
        parserProgress& operator--(int);
        parserProgress& operator++();
        parserProgress& operator++(int);
    };
    void parse(const std::vector<std::shared_ptr<Lexer::Token>> &data);
}
#endif // PARSER_H
