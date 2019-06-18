#include "parser_for_statement.h"

Parser::ForStatement::ForStatement(std::shared_ptr<Expression> p,std::shared_ptr<Expression> c,std::shared_ptr<Expression> i,std::shared_ptr<Line> l):
    pre(p),
    condition(c),
    inc(i),
    code(l){}
