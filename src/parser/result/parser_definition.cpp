#include "parser_definition.h"


Parser::Definition::Definition(ParserDefinitionType_t t,std::shared_ptr<ParserResultPart> d):type(t),def(d){
    
}
