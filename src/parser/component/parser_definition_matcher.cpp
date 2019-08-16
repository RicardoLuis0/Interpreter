#include "parser_definition_matcher.h"

#include "parser_var_type_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"
#include "parser_function_definition_matcher.h"
#include "parser_variable_definition_matcher.h"

//Definition = FunctionDefinition | VariableDefinition , symbol ';' ;

using namespace Parser;

std::shared_ptr<Definition> DefinitionMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    int location_backup;
    try{
        location_backup=p.location;
        return std::make_shared<Definition>(DEFINITION_FUNC,FunctionDefinitionMatcher().makeMatch(p),line_start,p.get_line(-1));
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        std::shared_ptr<VarType> vt=nullptr;
        try{
            vt=VarTypeMatcher().makeMatch(p);
        }catch(MyExcept::NoMatchException &e){
            vt=nullptr;
        }
        if(vt&&p.peekType(Lexer::TOKEN_TYPE_WORD)&&p.peekSymbol(SYMBOL_PARENTHESIS_OPEN,1))throw;//if is function definition rethrow
        p.location=location_backup;
        std::shared_ptr<VariableDefinition> vdef=VariableDefinitionMatcher().makeMatch(p);
        if(!p.isSymbol(SYMBOL_SEMICOLON))MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");//variable definition must end in semicolon
        return std::make_shared<Definition>(DEFINITION_VAR,vdef,line_start,p.get_line(-1));
    }
}
