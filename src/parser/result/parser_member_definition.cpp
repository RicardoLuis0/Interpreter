#include "parser_member_definition.h"

using namespace Parser;

MemberDefinition::MemberDefinition(bool o,member_scope_t s,member_type_t t,std::shared_ptr<ParserResultPart> m,int ls,int le):
    ParserResultPart(ls,le),
    is_override(o),
    scope(s),
    type(t),
    member(m){
}
