#include "parser_member_definition.h"

using namespace Parser;

MemberDefinition::MemberDefinition(bool o,member_scope_t s,member_modifier_t m,member_type_t t,std::shared_ptr<ParserResultPart> mb,int ls,int le):
    ParserResultPart(ls,le),
    is_override(o),
    scope(s),
    mod(m),
    type(t),
    member(mb){
}
