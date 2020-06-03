#include "Parser/StructDefinition.h"

#include <iostream>

using namespace Parser;

StructDefinition::StructDefinition(parserProgress &p){
    throw std::runtime_error("StructDefinition unimplemented");//TODO re-add StructDefinition in new parser
}

StructDefinition::StructDefinition(std::string n,std::vector<std::shared_ptr<MemberDefinition>> m,int ls,int le):
    ParserResultPart(ls,le),
    name(n),
    members(m){
}

std::string StructDefinition::getSource(int indent){
    throw std::runtime_error("struct definition de-parsing not implemented yet");
}

void StructDefinition::print(int){
    throw std::runtime_error("struct definition printing not implemented yet");
}
