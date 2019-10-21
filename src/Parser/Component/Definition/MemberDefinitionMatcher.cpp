#include "Parser/MemberDefinitionMatcher.h"
#include "symbols_keywords.h"
#include "Parser/VarTypeMatcher.h"
#include "MyExcept/MyExcept.h"
#include "Parser/FunctionDefinitionMatcher.h"
#include "Parser/VariableDefinitionMatcher.h"

using namespace Parser;

//MemberDefinition = [ keyword 'override' ] [ keyword 'public' | keyword 'protected' | keyword 'private' ] , [ keyword 'static' | keyword 'virtual' ] , ( VariableDefinition , symbol ';' | FunctionDefinition );

std::shared_ptr<MemberDefinition> MemberDefinitionMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    bool is_override=p.isKeyword(KEYWORD_OVERRIDE);
    std::shared_ptr<Lexer::KeywordToken> kw=p.isKeyword({KEYWORD_PUBLIC,KEYWORD_PROTECTED,KEYWORD_PRIVATE});
    member_scope_t scope;
    if(kw){
        switch(kw->get_keyword_type()){
        case KEYWORD_PUBLIC:
            scope=MEMBER_SCOPE_PUBLIC;
            break;
        case KEYWORD_PROTECTED:
            scope=MEMBER_SCOPE_PROTECTED;
            break;
        case KEYWORD_PRIVATE:
            scope=MEMBER_SCOPE_PRIVATE;
            break;
        }
    }else{
        scope=MEMBER_SCOPE_DEFAULT;
    }
    kw=p.isKeyword({KEYWORD_STATIC,KEYWORD_VIRTUAL});\
    member_modifier_t mod;
    if(kw){
        switch(kw->get_keyword_type()){
        case KEYWORD_STATIC:
            mod=MEMBER_MOD_STATIC;
            break;
        case KEYWORD_VIRTUAL:
            mod=MEMBER_MOD_VIRTUAL;
            break;
        }
    }else{
        mod=MEMBER_MOD_NONE;
    }
    int location_backup;
    try{
        location_backup=p.location;
        return std::make_shared<MemberDefinition>(is_override,scope,mod,MEMBER_TYPE_FUNCTION,FunctionDefinitionMatcher().makeMatch(p),line_start,p.get_line(-1));
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
        std::shared_ptr<VariableDefinition> vdef=VariableDefinitionMatcher().makeMatch(p);
        if(!p.isSymbol(SYMBOL_SEMICOLON))MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");
        return std::make_shared<MemberDefinition>(is_override,scope,mod,MEMBER_TYPE_VARIABLE,vdef,line_start,p.get_line(-1));
    }
}
