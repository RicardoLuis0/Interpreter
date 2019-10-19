#include "Parser/FunctionCall.h"

using namespace Parser;

FunctionCall::FunctionCall(std::string id,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id),arguments(args){
}
