#ifndef PARSER_EXPRESSION_OPERATOR_PRECEDENCE_H
#define PARSER_EXPRESSION_OPERATOR_PRECEDENCE_H

#include "parser_expression.h"

namespace Parser {
    std::shared_ptr<Expression> order_expression(std::shared_ptr<Expression>);
}
#endif // PARSER_EXPRESSION_OPERATOR_PRECEDENCE_H
