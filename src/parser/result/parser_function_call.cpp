#include "parser_function_call.h"

Parser::FunctionCall::FunctionCall(std::shared_ptr<Lexer::WordToken> id,std::shared_ptr<ExpressionList> args):identifier(id->get_literal()),arguments(args){
}
