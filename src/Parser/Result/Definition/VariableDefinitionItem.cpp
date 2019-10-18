#include "parser_variable_definition_item.h"

using namespace Parser;

VariableDefinitionItem::VariableDefinitionItem(std::string s,int ls,int le):ParserResultPart(ls,le),name(s),value(nullptr){
}

VariableDefinitionItem::VariableDefinitionItem(std::shared_ptr<Lexer::WordToken> t,std::shared_ptr<Expression> e,int ls,int le):ParserResultPart(ls,le),name(t->get_literal()),value(e){
}
