#include "parser_return_statement.h"

using namespace Parser;

ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expr,int ls,int le):ParserResultPart(ls,le),value(expr){}
