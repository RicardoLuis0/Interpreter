#include "parser_variable_definition_matcher.h"

#include "symbols_keywords.h"
#include "token_type.h"
#include "parser_expression_matcher.h"
#include "my_except.h"

//FunctionDefinition = identifier , symbol '(' , [ FunctionDefinitionParameter { symbol ',' , FunctionDefinitionParameter } ] , symbol ')' ;

std::shared_ptr<Parser::VariableDefinition> Parser::VariableDefinitionMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<Lexer::Token> t;
    if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD)))MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Expression> e=nullptr;
    if(p.isSymbol(SYMBOL_ASSIGNMENT)){
        e=ExpressionMatcher().makeMatch(p);
    }
    return std::make_shared<VariableDefinition>(std::static_pointer_cast<Lexer::WordToken>(t),e);
}
