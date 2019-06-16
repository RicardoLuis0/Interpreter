#include "parser_expression_group_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"
#include "parser_expression_matcher.h"

// ExpressionGroup = symbol '(' ,  [ Expression ] , symbol ')' ;

std::shared_ptr<Parser::ExpressionGroup> Parser::ExpressionGroupMatcher::makeMatch(parserProgress &p){
    if(p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        int location_backup=p.location;
        std::shared_ptr<Expression> expression(nullptr);
        try{
            expression=ExpressionMatcher().makeMatch(p);
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            if(p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
                return std::make_shared<ExpressionGroup>(nullptr);
            }else{
                throw;
            }
        }
        if(p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            return std::make_shared<ExpressionGroup>(expression);
        }else{
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
        }
    }else{
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
}
