#include "parser_unary_operation.h"

Parser::UnaryOperation::UnaryOperation(std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<ExpressionTerm> et):unary_operator(st),term(et){
}
