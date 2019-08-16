#include "parser_expression_group_matcher.h"
#include "my_except.h"
#include "symbols_keywords.h"
#include "parser_expression_matcher.h"

// ExpressionGroup = symbol '(' , [ Expression ] , symbol ')' ;

using namespace Parser;

std::shared_ptr<ExpressionGroup> ExpressionGroupMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    if(p.isSymbol(SYMBOL_PARENTHESIS_OPEN)){
        int location_backup=p.location;
        std::shared_ptr<Expression> expression(nullptr);
        try{
            expression=ExpressionMatcher().makeMatch(p);
        }catch(MyExcept::NoMatchException &e){
            p.location=location_backup;
            if(p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
                return std::make_shared<ExpressionGroup>(nullptr,line_start,p.get_line(-1));//don't know if i should still allow empty ExpressionGroups
            }else{
                throw;
            }
        }
        if(p.isSymbol(SYMBOL_PARENTHESIS_CLOSE)){
            return std::make_shared<ExpressionGroup>(expression,line_start,p.get_line(-1));
        }else{
            throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected ')', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
        }
    }else{
        throw MyExcept::NoMatchException(p.get_nothrow_nonull()->line,"expected '(', got '"+p.get_nothrow_nonull()->get_formatted()+"'");
    }
}
