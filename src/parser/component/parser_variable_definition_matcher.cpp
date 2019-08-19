#include "parser_variable_definition_matcher.h"

#include "symbols_keywords.h"
#include "lexer_token_type.h"
#include "parser_expression_matcher.h"
#include "my_except.h"
#include "parser_var_type_matcher.h"
#include "parser_variable_definition_item_matcher.h"

//VariableDefinition = VarType , VariableDefinitionItem { symbol ',' , VariableDefinitionItem } ;

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
