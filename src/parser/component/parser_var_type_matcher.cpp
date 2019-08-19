#include "parser_var_type_matcher.h"

#include "lexer_keyword_token.h"
#include "symbols_keywords.h"
#include "my_except.h"
#include "parser_expression_matcher.h"

//VarType = ( [ keyword 'unsigned' | keyword 'signed' ] , ( keyword 'any' | keyword 'void' | keyword 'int' | keyword 'float' | keyword 'string' ) ) , { symbol '[' , [ Expression ] , symbol ']' } ;

using namespace Parser;

std::shared_ptr<VarType> VarTypeMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    std::shared_ptr<Lexer::KeywordToken> kw=p.isKeyword({KEYWORD_SIGNED,KEYWORD_UNSIGNED});
    std::shared_ptr<VarType> vt;
    bool has_sign=false;
    bool sign=true;
    if(kw){
        has_sign=true;
        sign=kw->get_keyword_type()==KEYWORD_SIGNED;
    }
    kw=p.isKeyword({KEYWORD_ANY,KEYWORD_VOID,KEYWORD_INT,KEYWORD_FLOAT,KEYWORD_STRING});
    if(kw){
        vt=std::make_shared<VarType>(kw,has_sign,sign,line_start,p.get_line(-1));
    }else{
        if(has_sign){
            p--;
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected variable type, got '"+p.get_nothrow_nonull()->get_literal()+"'");
        }else{
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected variable type, got '"+p.get_nothrow_nonull()->get_literal()+"'");
        }
    }
    if(vt){
        while(p.isSymbol(SYMBOL_SQUARE_BRACKET_OPEN)){
            try{
                vt->array_sizes.insert(vt->array_sizes.begin(),ExpressionMatcher().makeMatch(p));
            }catch(MyExcept::NoMatchException &e){
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
