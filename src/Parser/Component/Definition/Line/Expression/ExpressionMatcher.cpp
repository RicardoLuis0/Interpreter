#include "parser_expression_matcher.h"
#include "my_except.h"
#include "parser_expression_term_matcher.h"
#include "parser_expression_group_matcher.h"
#include "parser_binary_operation_matcher.h"

#include "parser_expression_operator_precedence.h"

//Expression = BinaryOperation |  ExpressionTerm ;

using namespace Parser;

std::shared_ptr<Expression> ExpressionMatcher::makeMatch(parserProgress &p){
    int line_start=p.get_line();
    int location_backup=p.location;
    try{
        return order_expression(std::make_shared<Expression>(BinaryOperationMatcher().makeMatch(p),EXPRESSION_BINARY_OPERATION,line_start,p.get_line(-1)));//order with operator precedence, WIP?
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        auto term=std::make_shared<Expression>(ExpressionTermMatcher().makeMatch(p),EXPRESSION_TERM,line_start,p.get_line(-1));
        if(BinaryOperationMatcher().checkIsBinaryOperator(p)){
           throw;//if it is a valid expression term followed by a valid binary operator, then it must be a binary operation, so throw previous error
        }
        return term;
    }
}