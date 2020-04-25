#ifndef PARSER_FOR_STATEMENT_H
#define PARSER_FOR_STATEMENT_H

#include "Parser/ParserResultPart.h"
#include "Parser/Line.h"
#include "Parser/Expression.h"
#include "Parser/VariableDefinition.h"

namespace Parser{
    class ForStatement:public ParserResultPart{
    public:
        ForStatement(parserProgress&);
        ForStatement(std::shared_ptr<Expression> pre,std::shared_ptr<VariableDefinition> vardef_pre,std::shared_ptr<Expression> condition,std::shared_ptr<Expression> inc,std::shared_ptr<Line> code,int line_start,int line_end);
        std::shared_ptr<Expression> pre,condition,inc;
        std::shared_ptr<VariableDefinition> vardef_pre;
        std::shared_ptr<Line> code;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_FOR_STATEMENT_H
