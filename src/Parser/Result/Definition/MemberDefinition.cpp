#include "Parser/MemberDefinition.h"

#include <iostream>

using namespace Parser;

MemberDefinition::MemberDefinition(bool o,member_scope_t s,member_modifier_t m,member_type_t t,std::shared_ptr<ParserResultPart> mb,int ls,int le):
    ParserResultPart(ls,le),
    is_override(o),
    scope(s),
    mod(m),
    type(t),
    member(mb){
}

std::string MemberDefinition::getSource(){
    throw std::runtime_error("member definition de-parsing not implemented yet");
}

void MemberDefinition::print(int depth){
    throw std::runtime_error("member definition printing not implemented yet");
}
