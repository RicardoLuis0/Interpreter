#include "parser_function_call_matcher.h"

#include "symbols_keywords.h"
#include "parser_expression_list_matcher.h"
#include "my_except.h"


//FunctionCall = identifier , symbol '(' , [ ExpressionList ] , symbol ')' ;

using namespace Parser;

std::shared_ptr<FunctionCall> FunctionCallMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Lexer::Token> identifier=p.isType(Lexer::TOKEN_TYPE_WORD);
    if(!identifier) throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    int location_backup=p.location;
    std::shared_ptr<ExpressionList> arguments(nullptr);
    try{
        arguments = ExpressionListMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            throw;
        }
        arguments=nullptr;
        /*else{
            return std::make_shared<FunctionCall>(std::static_pointer_cast<Lexer::WordToken>(identifier),nullptr,line_start,p.get_line(-1));
        }*/
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    return std::make_shared<FunctionCall>(std::static_pointer_cast<Lexer::WordToken>(identifier),arguments,line_start,p.get_line(-1));
}
