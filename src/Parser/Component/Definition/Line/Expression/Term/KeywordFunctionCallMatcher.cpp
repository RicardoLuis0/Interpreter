#include "Parser/KeywordFunctionCallMatcher.h"
#include "symbols_keywords.h"
#include "Parser/VarTypeMatcher.h"
#include "Parser/ExpressionListMatcher.h"
#include "MyExcept/MyExcept.h"

//KeywordFunctionCall = ( keyword 'cast' | keyword 'is' | keyword 'typeof' | keyword 'type' ) , [ symbol '<' , VarType , symbol '>' ] , symbol '(' , ExpressionList , symbol ')' ;

using namespace Parser;

std::shared_ptr<KeywordFunctionCall> KeywordFunctionCallMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Lexer::KeywordToken> identifier=p.isKeyword({KEYWORD_IS,KEYWORD_CAST,KEYWORD_TYPEOF,KEYWORD_TYPE});
    if(!identifier)throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"not a keyword function call");
    std::shared_ptr<VarType> type=nullptr;
    if(p.isSymbol(SYMBOL_LOWER)){
        type=VarTypeMatcher().makeMatch(p);
        if(!p.isSymbol(SYMBOL_GREATER)){
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '>', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
        }
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    int location_backup=p.location;
    std::shared_ptr<ExpressionList> arguments=nullptr;
    try{
        arguments = ExpressionListMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            throw;
        }
        arguments=nullptr;
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    return std::make_shared<KeywordFunctionCall>(identifier,type,arguments,line_start,p.get_line(-1));
}
