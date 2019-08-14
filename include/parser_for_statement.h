#ifndef PARSER_FOR_STATEMENT_H
#define PARSER_FOR_STATEMENT_H

#include "parser_result_part.h"
#include "parser_line.h"
#include "parser_expression.h"
#include "parser_variable_definition.h"

namespace Parser{
    class ForStatement:public ParserResultPart{
    public:
        ForStatement(std::shared_ptr<Expression> pre,std::shared_ptr<VariableDefinition> vardef_pre,std::shared_ptr<Expression> condition,std::shared_ptr<Expression> inc,std::shared_ptr<Line> code);
        std::shared_ptr<Expression> pre,condition,inc;
        std::shared_ptr<VariableDefinition> vardef_pre;
        std::shared_ptr<Line> code;
    };
}

#endif // PARSER_FOR_STATEMENT_H
