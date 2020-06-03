#include "Parser/ClassDefinition.h"

#include <iostream>

using namespace Parser;

ClassDefinition::ClassDefinition(parserProgress &){
    throw std::runtime_error("unimplemented");
}

ClassDefinition::ClassDefinition(int ls,int le):ParserResultPart(ls,le){
}
