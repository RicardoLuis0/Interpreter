#include "Parser/VariableDefinitionMatcher.h"

#include "symbols_keywords.h"
#include "Lexer/token_type.h"
#include "Parser/ExpressionMatcher.h"
#include "MyExcept/MyExcept.h"
#include "Parser/VarTypeMatcher.h"
#include "Parser/VariableDefinitionItemMatcher.h"

//VariableDefinition = VarType , VariableDefinitionItem , { symbol ',' , VariableDefinitionItem } ;

using namespace Parser;

std::shared_ptr<VariableDefinition> VariableDefinitionMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<VarType> vt=VarTypeMatcher().makeMatch(p);
    std::vector<std::shared_ptr<VariableDefinitionItem>> vars;
    do{
        vars.push_back(VariableDefinitionItemMatcher().makeMatch(p));
    }while(p.isSymbol(SYMBOL_COMMA));
    return std::make_shared<VariableDefinition>(vt,vars,line_start,p.get_line(-1));
}
