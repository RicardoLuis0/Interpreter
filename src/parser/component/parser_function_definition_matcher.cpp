#include "parser_function_definition_matcher.h"

#include "my_except.h"
#include "symbols_keywords.h"
#include "token_type.h"
#include "parser_function_definition_parameter_matcher.h"
#include "parser_var_type_matcher.h"
#include "parser_code_block_matcher.h"

//FunctionDefinition = VarType , identifier , symbol '(' , [ FunctionDefinitionParameter { symbol ',' , FunctionDefinitionParameter } ] , symbol ')' , CodeBlock ;

std::shared_ptr<Parser::FunctionDefinition> Parser::FunctionDefinitionMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<VarType> vt=VarTypeMatcher().makeMatch(p);
    std::shared_ptr<Lexer::Token> t;
    if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD)))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::vector<std::shared_ptr<FunctionDefinitionParameter>> params;
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    int location_backup;
    try{
        do{
            location_backup=p.location;
            params.push_back(FunctionDefinitionParameterMatcher().makeMatch(p));
        }while(p.isSymbol(SYMBOL_COMMA));
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<CodeBlock> code=CodeBlockMatcher().makeMatch(p);
    return std::make_shared<FunctionDefinition>(vt,std::static_pointer_cast<Lexer::WordToken>(t),params,code);
}
