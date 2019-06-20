#include "parser_function_call_matcher.h"

#include "symbols_keywords.h"
#include "parser_expression_list_matcher.h"
#include "my_except.h"


//FunctionCall = identifier , symbol '(' , [ ExpressionList ] , symbol ')' ;

std::shared_ptr<Parser::FunctionCall> Parser::FunctionCallMatcher::makeMatch(parserProgress &p){
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
        if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            throw;
        }else{
            return std::make_shared<FunctionCall>(std::static_pointer_cast<Lexer::WordToken>(identifier),nullptr);
        }
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
    return std::make_shared<FunctionCall>(std::static_pointer_cast<Lexer::WordToken>(identifier),arguments);
}
