#include "parser_function_call.h"

using namespace Parser;

FunctionCall::FunctionCall(std::shared_ptr<Lexer::WordToken> id,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id->get_literal()),arguments(args){
}
