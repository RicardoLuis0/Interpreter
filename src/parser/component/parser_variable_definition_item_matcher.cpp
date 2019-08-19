#include "parser_variable_definition_item_matcher.h"

#include "symbols_keywords.h"
#include "lexer_token_type.h"
#include "parser_expression_matcher.h"
#include "my_except.h"

//VariableDefinitionItem = identifier , [ symbol '=' , Expression ] ;

using namespace Parser;

std::shared_ptr<VariableDefinitionItem> VariableDefinitionItemMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Lexer::Token> t;
    if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD)))MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Expression> e=nullptr;
    if(p.isSymbol(SYMBOL_ASSIGNMENT)){
        e=ExpressionMatcher().makeMatch(p);
    }
    return std::make_shared<VariableDefinitionItem>(std::static_pointer_cast<Lexer::WordToken>(t),e,line_start,p.get_line(-1));
}
