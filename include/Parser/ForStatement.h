#ifndef PARSER_FOR_STATEMENT_H
#define PARSER_FOR_STATEMENT_H

#include "Parser/ResultPart.h"
#include "Parser/Line.h"
#include "Parser/Expression.h"
#include "Parser/VariableDefinition.h"

namespace Parser{
    class ForStatement:public ParserResultPart{
    public:
        ForStatement(std::shared_ptr<Expression> pre,std::shared_ptr<VariableDefinition> vardef_pre,std::shared_ptr<Expression> condition,std::shared_ptr<Expression> inc,std::shared_ptr<Line> code,int line_start,int line_end);
        std::shared_ptr<Expression> pre,condition,inc;
        std::shared_ptr<VariableDefinition> vardef_pre;
        std::shared_ptr<Line> code;
    };
}

#endif // PARSER_FOR_STATEMENT_H
