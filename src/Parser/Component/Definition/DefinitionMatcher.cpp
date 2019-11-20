#include "Parser/DefinitionMatcher.h"

#include "Parser/VarTypeMatcher.h"
#include "MyExcept/MyExcept.h"
#include "symbols_keywords.h"
#include "Parser/FunctionDefinitionMatcher.h"
#include "Parser/VariableDefinitionMatcher.h"
#include "Parser/StructDefinitionMatcher.h"

//Definition = StructDefinition | FunctionDefinition | VariableDefinition , symbol ';' ;

using namespace Parser;

std::shared_ptr<Definition> DefinitionMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    int location_backup;
    try{
        location_backup=p.location;
        auto sdef=StructDefinitionMatcher().makeMatch(p);
        return std::make_shared<Definition>(DEFINITION_STRUCT,sdef,line_start,p.get_line(-1));
    }catch(MyExcept::NoMatchException &){
        p.location=location_backup;
        if(p.peekKeyword(KEYWORD_STRUCT))throw;//rethrow if struct;
        try{
            location_backup=p.location;
            auto fdef=FunctionDefinitionMatcher().makeMatch(p);
            return std::make_shared<Definition>(DEFINITION_FUNC,fdef,line_start,p.get_line(-1));
        }catch(MyExcept::NoMatchException &){
            p.location=location_backup;
            std::shared_ptr<VarType> vt=nullptr;
            try{
                vt=VarTypeMatcher().makeMatch(p);
            }catch(MyExcept::NoMatchException &){
                vt=nullptr;
            }
            if(vt&&p.peekType(Lexer::TOKEN_TYPE_WORD)&&p.peekSymbol(SYMBOL_PARENTHESIS_OPEN,1))throw;//if is function definition rethrow
            p.location=location_backup;
            auto vdef=VariableDefinitionMatcher().makeMatch(p);
            if(!p.isSymbol(SYMBOL_SEMICOLON))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");//variable definition must end in semicolon
            return std::make_shared<Definition>(DEFINITION_VAR,vdef,line_start,p.get_line(-1));
        }
    }
}
