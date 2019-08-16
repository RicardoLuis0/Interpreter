#ifndef PARSER_RETURN_STATEMENT_H
#define PARSER_RETURN_STATEMENT_H

#include "parser_result_part.h"
#include "parser_expression.h"

namespace Parser{
    class ReturnStatement : public ParserResultPart {
        public:
            ReturnStatement(std::shared_ptr<Expression> value,int line_start,int line_end);
            std::shared_ptr<Expression> value;
    };
}

#endif // PARSER_RETURN_STATEMENT_H
