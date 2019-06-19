#include "parser_function_definition_matcher.h"

#include "parser_var_type.h"
#include "parser_var_type_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"

std::shared_ptr<Parser::FunctionDefinition> Parser::FunctionDefinitionMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<WordToken> t=p.isType(TOKEN_TYPE_WORD);
    if(t){
        if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
        if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
        return std::make_shared<FunctionDefinition>();
    }else{
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    }
}
