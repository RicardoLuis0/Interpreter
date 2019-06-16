#include "parser_expression.h"

Parser::Expression::Expression(std::shared_ptr<ParserResultPart> ptr,ExpressionType_t ptype):contents(ptr),type(ptype){
    
}
