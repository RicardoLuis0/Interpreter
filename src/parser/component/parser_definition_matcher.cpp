#include "parser_definition_matcher.h"

#include "parser_var_type.h"
#include "parser_var_type_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"
#include "parser_function_definition_matcher.h"

std::shared_ptr<Parser::Definition> Parser::DefinitionMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<Definition> def=std::make_shared<Definition>(VarTypeMatcher().makeMatch(p));
    while(1){
        int location_backup;
        try{
            location_backup=p.location;
            def->definitions.push_back({DEFINITION_FUNC,FunctionDefinitionMatcher().makeMatch(p)});
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            if(p.peekType(Lexer::TOKEN_TYPE_WORD)&&p.peekSymbol(SYMBOL_PARENTHESIS_OPEN))throw;//if is function definition rethrow
            //try variable definition
        }
        if(!p.isSymbol(SYMBOL_COMMA)){
            break;
        }
    }
    return def;
}
