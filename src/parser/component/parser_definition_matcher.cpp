#include "parser_definition_matcher.h"

#include "parser_var_type.h"
#include "parser_var_type_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"
#include "parser_function_definition_matcher.h"
#include "parser_variable_definition_matcher.h"

std::shared_ptr<Parser::Definition> Parser::DefinitionMatcher::makeMatch(parserProgress &p){
    int location_backup;
    try{
        location_backup=p.location;
        return std::make_shared<Definition>(DEFINITION_FUNC,FunctionDefinitionMatcher().makeMatch(p));
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        std::shared_ptr<VarType> vt=nullptr;
        try{
            vt=VarTypeMatcher().makeMatch(p);
        }catch(MyExcept::NoMatchException &e){
            vt=nullptr;
        }
        if(vt&&p.peekType(Lexer::TOKEN_TYPE_WORD)&&p.peekSymbol(SYMBOL_PARENTHESIS_OPEN))throw;//if is function definition rethrow
        p.location=location_backup;
        return std::make_shared<Definition>(DEFINITION_VAR,VariableDefinitionMatcher().makeMatch(p));
    }
}
