#include "Parser/Expression.h"
#include "Parser/ExpressionTerm.h"
#include "Parser/BinaryOperation.h"

#include "MyExcept/MyExcept.h"
#include "Parser/ParserExpressionOperatorPrecedence.h"

#include <iostream>

using namespace Parser;

Expression::Expression(parserProgress &p){
    line_start=p.get_line();
    contents=std::make_shared<ExpressionTerm>(p);
    type=EXPRESSION_TERM;
    line_end=p.get_line(-1);
    if(BinaryOperation::peekIsBinaryOperator(p)){
        auto binop=std::make_shared<BinaryOperation>(line_start,std::static_pointer_cast<ExpressionTerm>(contents),p);
        line_end=p.get_line(-1);
        auto expr=order_expression(std::make_shared<Expression>(binop,EXPRESSION_BINARY_OPERATION,line_start,line_end));//order with operator precedence, WIP?
        contents=expr->contents;
        type=expr->type;
    }
}

Expression::Expression(std::shared_ptr<ParserResultPart> ptr,ExpressionType_t ptype,int ls,int le):ParserResultPart(ls,le),contents(ptr),type(ptype){
    
}

std::string Expression::getSource(){
    return contents->getSource();
}

void Expression::print(int depth){
    std::string indent0=get_indent(depth);
    std::string indent1=get_indent(depth+1);
    std::cout<<indent0<<"Expression {\n";
    std::cout<<indent0<<".contents:\n";
    contents->print(depth+1);
    std::cout<<indent0<<"}\n";
}
