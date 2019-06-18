#include "parser_if_statement.h"

Parser::IfStatement::IfStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l):condition(cond),code(l){
}
