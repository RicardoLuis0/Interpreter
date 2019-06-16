#include "parser_expression_matcher.h"
#include "my_except.h"
#include "parser_expression_term_matcher.h"
#include "parser_expression_group_matcher.h"
#include "parser_binary_operation_matcher.h"

//Expression = BinaryOperation |  ExpressionTerm ;

std::shared_ptr<Parser::Expression> Parser::ExpressionMatcher::makeMatch(parserProgress &p){
    int location_backup=p.location;
    try{
        return std::make_shared<Expression>(BinaryOperationMatcher().makeMatch(p),EXPRESSION_BINARY_OPERATION);
    }catch(MyExcept::NoMatchException &e){
        p.location=location_backup;
        auto term=std::make_shared<Expression>(ExpressionTermMatcher().makeMatch(p),EXPRESSION_TERM);
        if(BinaryOperationMatcher().checkIsBinaryOperator(p)){
           throw;//if it is a valid expression term followed by a valid binary operator, then it must be a binary operation, so throw previous error
        }
        return term;
    }
}
