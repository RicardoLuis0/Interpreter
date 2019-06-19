#include "parser_variable_definition_item.h"

Parser::VariableDefinitionItem::VariableDefinitionItem(std::shared_ptr<Lexer::WordToken> t,std::shared_ptr<Expression> e):name(t),value(e){}
