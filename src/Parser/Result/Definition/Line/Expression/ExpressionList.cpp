#include "Parser/ExpressionList.h"

using namespace Parser;

ExpressionList::ExpressionList(std::vector<std::shared_ptr<Expression>> el,int ls,int le):ParserResultPart(ls,le),expression_list(el){
    
}
