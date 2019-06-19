#include "parser_definition_matcher.h"

#include "parser_var_type.h"
#include "parser_var_type_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"

std::shared_ptr<Parser::Definition> Parser::DefinitionMatcher::makeMatch(parserProgress &p){
    std::shared_ptr<Definition> def=std::make_shared<Definition>(VarTypeMatcher().makeMatch(p));
    while(1){
        try{
            //try variable definition
        }catch(MyExcept::NoMatchException &e){
            //try function definition
        }
        if(!p.isSymbol(SYMBOL_COMMA)){
            break;
        }
    }
}
