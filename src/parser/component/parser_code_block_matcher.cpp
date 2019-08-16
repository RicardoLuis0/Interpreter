#include "parser_code_block_matcher.h"

#include "symbols_keywords.h"
#include "my_except.h"
#include "parser_line.h"
#include "parser_line_matcher.h"

//CodeBlock = symbol '{' , { Line } , symbol '}' ;

using namespace Parser;

std::shared_ptr<CodeBlock> CodeBlockMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::vector<std::shared_ptr<Line>> lines;
    bool is_symbol=false;
    if(p.isSymbol(SYMBOL_CURLY_BRACKET_OPEN)){
        while(p.in_range(0)&&!(is_symbol=p.isSymbol(SYMBOL_CURLY_BRACKET_CLOSE))){
            lines.push_back(LineMatcher().makeMatch(p));
        }
        if(!p.in_range(0)&&!is_symbol){
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '}', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
        }
    }else{
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '{', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    return std::make_shared<CodeBlock>(lines,line_start,p.get_line(-1));
}
