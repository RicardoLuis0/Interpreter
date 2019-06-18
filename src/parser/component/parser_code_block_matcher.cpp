#include "parser_code_block_matcher.h"

#include "symbols_keywords.h"
#include "my_except.h"
#include "parser_line.h"
#include "parser_line_matcher.h"

//CodeBlock = symbol '{' , { Line } , symbol '}' ;

std::shared_ptr<Parser::CodeBlock> Parser::CodeBlockMatcher::makeMatch(parserProgress &p){
    std::vector<std::shared_ptr<Line>> lines;
    if(p.isSymbol(SYMBOL_CURLY_BRACKET_OPEN)){
        while(!p.isSymbol(SYMBOL_CURLY_BRACKET_CLOSE)){//TODO check for eof
            lines.push_back(LineMatcher().makeMatch(p));
        }
    }else{
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '{', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    return std::make_shared<CodeBlock>(lines);
}
