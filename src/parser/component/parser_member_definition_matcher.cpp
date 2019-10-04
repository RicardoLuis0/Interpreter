#include "parser_member_definition_matcher.h"

using namespace Parser;

//MemberDefinition = [ keyword 'override' ] [ keyword 'public' | keyword 'protected' | keyword 'private' ] , [ keyword 'static' | keyword 'virtual' ] , ( VariableDefinition , symbol ';' | FunctionDefinition );

std::shared_ptr<MemberDefinition> MemberDefinitionMatcher::makeMatch(parserProgress &p){
    //TODO
    throw std::runtime_error("unimplemented");
}
