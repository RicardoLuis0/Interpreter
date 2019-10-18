#include "parser_expression.h"

using namespace Parser;

Expression::Expression(std::shared_ptr<ParserResultPart> ptr,ExpressionType_t ptype,int ls,int le):ParserResultPart(ls,le),contents(ptr),type(ptype){
    
}
