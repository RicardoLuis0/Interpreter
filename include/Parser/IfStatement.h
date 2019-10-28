#ifndef PARSER_IF_STATEMENT_H
#define PARSER_IF_STATEMENT_H

#include "Parser/ParserResultPart.h"
#include "Parser/Line.h"
#include "Parser/Expression.h"
#include "Parser/ElseStatement.h"

namespace Parser{
    class IfStatement:public ParserResultPart{
    public:
        IfStatement(std::shared_ptr<Expression> condition,std::shared_ptr<Line> code,std::shared_ptr<ElseStatement> else_stmt,int line_start,int line_end);
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Line> code;
        std::shared_ptr<ElseStatement> else_stmt;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_IF_STATEMENT_H
