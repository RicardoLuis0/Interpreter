#include "Parser/VariableDefinition.h"

using namespace Parser;

VariableDefinition::VariableDefinition(std::shared_ptr<VarType> t,std::vector<std::shared_ptr<VariableDefinitionItem>> v,int ls,int le):ParserResultPart(ls,le),type(t),variables(v){}
