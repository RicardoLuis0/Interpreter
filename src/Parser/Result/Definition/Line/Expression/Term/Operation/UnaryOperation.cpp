#include "Parser/UnaryOperation.h"

using namespace Parser;

UnaryOperation::UnaryOperation(std::shared_ptr<Lexer::SymbolToken> st,std::shared_ptr<ExpressionTerm> et,int ls,int le):ParserResultPart(ls,le),unary_operator(st),term(et){
}
