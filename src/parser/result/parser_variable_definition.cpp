#include "parser_variable_definition.h"

Parser::VariableDefinition::VariableDefinition(std::shared_ptr<Lexer::WordToken> t,std::shared_ptr<Expression> e):name(t),value(e){}
