#include "Parser/BinaryOperation.h"

using namespace Parser;

BinaryOperation::BinaryOperation(std::shared_ptr<ExpressionTerm> et,std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<Expression> ex,int ls,int le):ParserResultPart(ls,le),term1(et),binary_operator(st),term2(ex){
    
}
