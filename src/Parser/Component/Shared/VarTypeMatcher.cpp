#include "Parser/VarTypeMatcher.h"

#include "Lexer/KeywordToken.h"
#include "symbols_keywords.h"
#include "MyExcept/MyExcept.h"
#include "Parser/ExpressionMatcher.h"

//VarType = [ keyword 'const' ] [ keyword 'unsigned' | keyword 'signed' ] , ( ( keyword 'pointer' , symbol '<' , ( VarType | symbol '?' ) , symbol '>' ) |  keyword 'any' | keyword 'type' | keyword 'void' | keyword 'int' | keyword 'char' | keyword 'float' | keyword 'string' ) , { symbol '[' , [ Expression ] , symbol ']' } ;

using namespace Parser;

std::shared_ptr<VarType> VarTypeMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<VarType> vt;
    bool is_const=p.isKeyword(KEYWORD_CONST);
    bool has_sign=false;
    bool sign=true;
    std::shared_ptr<Lexer::KeywordToken> kw=p.isKeyword({KEYWORD_SIGNED,KEYWORD_UNSIGNED});
    if(kw){
        has_sign=true;
        sign=kw->get_keyword_type()==KEYWORD_SIGNED;
    }
    kw=p.isKeyword({KEYWORD_POINTER,KEYWORD_ANY,KEYWORD_TYPE,KEYWORD_VOID,KEYWORD_INT,KEYWORD_CHAR,KEYWORD_FLOAT,KEYWORD_STRING});
    if(kw){
        std::shared_ptr<VarType> vt2=nullptr;
        if(kw->get_keyword_type()==KEYWORD_POINTER){
            if(!p.isSymbol(SYMBOL_LOWER)){
                throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '<', got '"+p.get_nothrow_nonull()->get_literal()+"'");
            }
            if(!p.isSymbol(SYMBOL_QUESTION_MARK)){
                vt2=makeMatch(p);
            }
            if(!p.isSymbol(SYMBOL_GREATER)){
                throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '>', got '"+p.get_nothrow_nonull()->get_literal()+"'");
            }
        }
        vt=std::make_shared<VarType>(kw,is_const,has_sign,sign,vt2,line_start,p.get_line(-1));
    }else{
        if(has_sign){
            p--;
        }
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected variable type, got '"+p.get_nothrow_nonull()->get_literal()+"'");
    }
    if(vt){
        while(p.isSymbol(SYMBOL_SQUARE_BRACKET_OPEN)){
            try{
                vt->array_sizes.insert(vt->array_sizes.begin(),ExpressionMatcher().makeMatch(p));
            }catch(MyExcept::NoMatchException &){
                vt->array_sizes.insert(vt->array_sizes.begin(),nullptr);
            }
            if(!p.isSymbol(SYMBOL_SQUARE_BRACKET_CLOSE)){
                throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ']', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
            }
        }
        return vt;
    }else{
        throw std::runtime_error("unexpected nullptr");
    }
}
