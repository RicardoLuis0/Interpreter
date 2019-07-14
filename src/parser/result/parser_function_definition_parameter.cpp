#include "parser_function_definition_parameter.h"

Parser::FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> v,std::shared_ptr<Lexer::WordToken> i,bool ref):type(v),name(i->get_literal()),is_reference(ref){}


Parser::FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> vt,std::string n,bool ref):type(vt),name(n),is_reference(ref){}
