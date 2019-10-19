#include "Parser/StructDefinitionMatcher.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"
#include "Parser/MemberDefinitionMatcher.h"
#include "Lexer/WordToken.h"

using namespace Parser;

//StructDefinition = keyword 'struct' , identifier , symbol '{' , { MemberDefinition } , symbol '}' ;

std::shared_ptr<StructDefinition> StructDefinitionMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    if(p.isKeyword(KEYWORD_STRUCT)){
        std::shared_ptr<Lexer::Token> t;
        std::vector<std::shared_ptr<MemberDefinition>> members;
        if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD)))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
        if(!p.isSymbol(SYMBOL_CURLY_BRACKET_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '{', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
        while(!p.isSymbol(SYMBOL_CURLY_BRACKET_CLOSE)){
            members.push_back(MemberDefinitionMatcher().makeMatch(p));
        }
        return std::make_shared<StructDefinition>(std::static_pointer_cast<Lexer::WordToken>(t)->get_literal(),members,line_start,p.get_line(-1));
    }else{
        throw MyExcept::NoMatchException(-1,"not a struct");
    }
}
