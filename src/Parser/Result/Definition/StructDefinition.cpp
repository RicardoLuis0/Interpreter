#include "Parser/StructDefinition.h"

using namespace Parser;

StructDefinition::StructDefinition(std::string n,std::vector<std::shared_ptr<MemberDefinition>> m,int ls,int le):
    ParserResultPart(ls,le),
    name(n),
    members(m){
}
