#include "parser_function_definition_parameter.h"

using namespace Parser;

FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> v,std::shared_ptr<Lexer::WordToken> i,bool ref,int ls,int le):ParserResultPart(ls,le),type(v),name(i->get_literal()),is_reference(ref){}

FunctionDefinitionParameter::FunctionDefinitionParameter(std::shared_ptr<VarType> vt,std::string n,bool ref,int ls,int le):ParserResultPart(ls,le),type(vt),name(n),is_reference(ref){}
