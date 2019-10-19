#include "Parser/ForStatementMatcher.h"

#include "Parser/ExpressionMatcher.h"
#include "Parser/LineMatcher.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"
#include "Parser/VariableDefinitionMatcher.h"

//ForStatement = keyword 'for' , symbol '(' , [ Expression | VariableDefinition ] , symbol ';' , [ Expression ] , symbol ';' , [ Expression ] , symbol ')' , Line ;

using namespace Parser;

std::shared_ptr<ForStatement> ForStatementMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Expression> pre=nullptr,cond=nullptr,inc=nullptr;
    std::shared_ptr<VariableDefinition> vardef_pre=nullptr;
    if(!p.isKeyword(KEYWORD_FOR))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected 'for', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    if(!p.isSymbol(SYMBOL_PARENTHESIS_OPEN))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    int location_backup=p.location;
    try{
        pre=ExpressionMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        pre=nullptr;
        try{
            vardef_pre=VariableDefinitionMatcher().makeMatch(p);
        }catch(MyExcept::NoMatchException &e){
            vardef_pre=nullptr;
            p.location=location_backup;
            if(!p.peekSymbol(SYMBOL_SEMICOLON))throw;//if next symbol isn't a semicolon, rethrow
        }
    }
    if(!p.isSymbol(SYMBOL_SEMICOLON))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    location_backup=p.location;
    try{
        cond=ExpressionMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_SEMICOLON))throw;//if next symbol isn't a semicolon, rethrow
        cond=nullptr;
    }
    if(!p.isSymbol(SYMBOL_SEMICOLON))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ';', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    location_backup=p.location;
    try{
        inc=ExpressionMatcher().makeMatch(p);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        if(!p.peekSymbol(SYMBOL_PARENTHESIS_CLOSE))throw;//if next symbol isn't a ')', rethrow
        inc=nullptr;
    }
    if(!p.isSymbol(SYMBOL_PARENTHESIS_CLOSE))throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_literal()+"'");
    std::shared_ptr<Line> line=LineMatcher().makeMatch(p);
    return std::make_shared<ForStatement>(pre,vardef_pre,cond,inc,line,line_start,p.get_line(-1));
}
