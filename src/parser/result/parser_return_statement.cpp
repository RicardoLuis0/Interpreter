#include "parser_return_statement.h"

Parser::ReturnStatement::ReturnStatement(std::shared_ptr<Expression> expr):value(expr){}
