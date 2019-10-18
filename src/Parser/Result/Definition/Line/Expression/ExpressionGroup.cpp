#include "parser_expression_group.h"

using namespace Parser;

ExpressionGroup::ExpressionGroup(std::shared_ptr<Expression> expr,int ls,int le):ParserResultPart(ls,le),contents(expr){
    
}
