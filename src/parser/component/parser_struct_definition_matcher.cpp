#include "parser_struct_definition_matcher.h"
#include "symbols_keywords.h"

using namespace Parser;

//StructDefinition = keyword 'struct' , symbol '{' , { MemberDefinition } , symbol '}' ;

std::shared_ptr<StructDefinition> StructDefinitionMatcher::makeMatch(parserProgress &p){
    if(p.isKeyword(KEYWORD_STRUCT)){
        
    }else{
        throw MyExcept::NoMatchException(-1,"not a struct");
    }
    //TODO
}
