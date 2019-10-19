#include "Parser/KeywordFunctionCall.h"


using namespace Parser;

KeywordFunctionCall::KeywordFunctionCall(std::shared_ptr<Lexer::KeywordToken> id,std::shared_ptr<VarType> type,std::shared_ptr<ExpressionList> args,int ls,int le):ParserResultPart(ls,le),identifier(id),extra_type(type),arguments(args){
    
}
