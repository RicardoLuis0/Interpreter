#include "parser_code_block_matcher.h"

#include "symbols_keywords.h"
#include "my_except.h"

//CodeBlock = symbol '{' , { Line } , symbol '}' ;

std::shared_ptr<Parser::CodeBlock> Parser::CodeBlockMatcher::makeMatch(parserProgress &p){
    if(p.isSymbol(SYMBOL_CURLY_BRACKET_OPEN)){
       
    }else{
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    throw std::runtime_error("unimplemented");
    //TODO
}

