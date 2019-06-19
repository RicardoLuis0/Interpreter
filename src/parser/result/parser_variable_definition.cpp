#include "parser_variable_definition.h"

Parser::VariableDefinition::VariableDefinition(std::shared_ptr<VarType> t,std::vector<std::shared_ptr<VariableDefinitionItem>> v):type(t),variables(v){}
