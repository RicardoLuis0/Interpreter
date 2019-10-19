#ifndef PARSER_STATEMENT_H
#define PARSER_STATEMENT_H

#include <memory>
#include "Parser/ResultPart.h"

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
            Statement(std::shared_ptr<ParserResultPart> statement,ParserStatementType_t type,int line_start,int line_end);
            std::shared_ptr<ParserResultPart> statement;
            const ParserStatementType_t type;
        protected:
        private:
    };
}
#endif // PARSER_STATEMENT_H
