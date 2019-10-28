#ifndef PARSER_WHILE_STATEMENT_H
#define PARSER_WHILE_STATEMENT_H

#include "Parser/ParserResultPart.h"
#include "Parser/Line.h"
#include "Parser/Expression.h"

namespace Parser{
    class WhileStatement:public ParserResultPart{
    public:
        WhileStatement(std::shared_ptr<Expression> condition,std::shared_ptr<Line> code,int line_start,int line_end);
        std::shared_ptr<Expression> condition;
        std::shared_ptr<Line> code;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_WHILE_STATEMENT_H
