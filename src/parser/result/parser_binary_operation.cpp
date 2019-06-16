#include "parser_binary_operation.h"

Parser::BinaryOperation::BinaryOperation(std::shared_ptr<ExpressionTerm> et,std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<Expression> ex):term1(et),binary_operator(st),term2(ex){
    
}
