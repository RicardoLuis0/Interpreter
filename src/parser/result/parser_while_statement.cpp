#include "parser_while_statement.h"

Parser::WhileStatement::WhileStatement(std::shared_ptr<Expression> cond,std::shared_ptr<Line> l):condition(cond),code(l){
}

