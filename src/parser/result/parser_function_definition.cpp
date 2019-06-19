#include "parser_function_definition.h"

Parser::FunctionDefinition::FunctionDefinition(std::shared_ptr<Lexer::WordToken> t,std::vector<std::shared_ptr<FunctionDefinitionParameter>> p):name(t),parameters(p){}
