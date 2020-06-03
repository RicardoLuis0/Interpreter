#ifndef PARSER_RETURN_STATEMENT_H
#define PARSER_RETURN_STATEMENT_H

#include "Parser/ParserResultPart.h"
#include "Parser/Expression.h"

namespace Parser{
    class ReturnStatement : public ParserResultPart {
    public:
        ReturnStatement(parserProgress&);
        ReturnStatement(std::shared_ptr<Expression> value,int line_start,int line_end);
        std::shared_ptr<Expression> value;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_RETURN_STATEMENT_H
