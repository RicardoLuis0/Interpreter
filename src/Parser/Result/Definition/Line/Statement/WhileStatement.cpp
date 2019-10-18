#include "parser_while_statement.h"

using namespace Parser;

WhileStatement::WhileStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),condition(cond),code(l){
}

