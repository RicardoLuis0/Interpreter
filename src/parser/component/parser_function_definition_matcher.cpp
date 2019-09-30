#include "parser_function_definition_matcher.h"

#include "my_except.h"
#include "symbols_keywords.h"
#include "lexer_token_type.h"
#include "parser_function_definition_parameter_matcher.h"
#include "parser_var_type_matcher.h"
#include "parser_code_block_matcher.h"

//FunctionDefinition = VarType , identifier , symbol '(' , [ FunctionDefinitionParameter { symbol ',' , FunctionDefinitionParameter } ] , [ [ VarType ] , symbol '...' , identifier ] , symbol ')' , CodeBlock ;

using namespace Parser;

std::shared_ptr<FunctionDefinition> FunctionDefinitionMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<VarType> vt=VarTypeMatcher().makeMatch(p);
    std::shared_ptr<Lexer::Token> t;
    if(!(t=p.isType(Lexer::TOKEN_TYPE_WORD)))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::vector<std::shared_ptr<FunctionDefinitionParameter>> params;
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    int location_backup;
    bool variadic;
    std::shared_ptr<VarType> variadic_type=nullptr;
    std::shared_ptr<Lexer::Token> variadic_ident=nullptr;
    try{
        do{
            location_backup=p.location;
            params.push_back(FunctionDefinitionParameterMatcher().makeMatch(p));
        }while(p.isSymbol(SYMBOL_COMMA));
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            try{
                location_backup=p.location;
                variadic_type=VarTypeMatcher().makeMatch(p);
            }catch(MyExcept::NoMatchException &e){
                p.location=location_backup;
            }
            if(!p.isSymbol(SYMBOL_VARIADIC)) throw;
            if(!(variadic_ident=p.isType(Lexer::TOKEN_TYPE_WORD))) throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected identifier, got '"+p.get_nothrow_nonull()->get_literal()+"'");
            variadic=true;
        }
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<CodeBlock> code=CodeBlockMatcher().makeMatch(p);
    return std::make_shared<FunctionDefinition>(vt,std::static_pointer_cast<Lexer::WordToken>(t),params,variadic,variadic_type,variadic_ident,code,line_start,p.get_line(-1));
}
