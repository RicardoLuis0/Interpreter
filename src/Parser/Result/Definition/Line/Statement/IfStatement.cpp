#include "Parser/IfStatement.h"

using namespace Parser;

IfStatement::IfStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l,std::shared_ptr<ElseStatement> es,int ls,int le):ParserResultPart(ls,le),condition(cond),code(l),else_stmt(es){
}
