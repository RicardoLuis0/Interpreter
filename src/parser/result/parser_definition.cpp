#include "parser_definition.h"

using namespace Parser;

Definition::Definition(ParserDefinitionType_t t,std::shared_ptr<ParserResultPart> d,int ls,int le):ParserResultPart(ls,le),type(t),def(d){
    
}
