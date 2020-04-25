#ifndef PARSER_STATEMENT_H
#define PARSER_STATEMENT_H

#include <memory>
#include "Parser/ParserResultPart.h"

namespace Parser{
    enum ParserStatementType_t{
        STATEMENT_IF,
        STATEMENT_WHILE,
        STATEMENT_FOR,
        STATEMENT_RETURN,
        STATEMENT_BREAK,
        STATEMENT_CONTINUE,
    };
    class Statement : public ParserResultPart {
    public:
        Statement(parserProgress&);
        Statement(std::shared_ptr<ParserResultPart> statement,ParserStatementType_t type,int line_start,int line_end);
        std::shared_ptr<ParserResultPart> statement;
        ParserStatementType_t type;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    protected:
    private:
    };
}
#endif // PARSER_STATEMENT_H
