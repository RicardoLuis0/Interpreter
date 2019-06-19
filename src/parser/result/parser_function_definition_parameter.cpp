#include "parser_function_definition_parameter.h"

Parser::FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> v,std::shared_ptr<Lexer::WordToken> i):type(v),name(i){}
