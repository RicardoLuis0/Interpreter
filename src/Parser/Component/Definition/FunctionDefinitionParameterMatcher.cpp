#include "parser_function_definition_parameter_matcher.h"

#include "parser_var_type.h"
#include "parser_var_type_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"
#include "lexer_token_type.h"

//FunctionDefinitionParameter = VarType , [ symbol '&' ] , identifier ;

using namespace Parser;

std::shared_ptr<FunctionDefinitionParameter> FunctionDefinitionParameterMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<VarType> vt=VarTypeMatcher().makeMatch(p);
    bool ref=p.isSymbol(SYMBOL_BITWISE_AND);
    std::shared_ptr<Lexer::Token> t;
    if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD)))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    return std::make_shared<FunctionDefinitionParameter>(vt,std::static_pointer_cast<Lexer::WordToken>(t),ref,line_start,p.get_line(-1));
}
