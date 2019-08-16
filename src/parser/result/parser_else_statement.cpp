#include "parser_else_statement.h"

using namespace Parser;

ElseStatement::ElseStatement(std::shared_ptr<Line> l,int ls,int le):ParserResultPart(ls,le),code(l){
}

