#include "parser_if_statement.h"

Parser::IfStatement::IfStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l,std::shared_ptr<ElseStatement> es):condition(cond),code(l),else_stmt(es){
}
