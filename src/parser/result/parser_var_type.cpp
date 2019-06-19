#include "parser_var_type.h"

Parser::VarType::VarType(std::shared_ptr<Lexer::KeywordToken> ptr):primitive(ptr),type(VARTYPE_PRIMITIVE){}
