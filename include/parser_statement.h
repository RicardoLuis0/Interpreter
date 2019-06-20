#ifndef PARSER_STATEMENT_H
#define PARSER_STATEMENT_H

#include <memory>
#include "parser_result_part.h"

namespace Parser{
    enum ParserStatementType_t{
        STATEMENT_IF,
        STATEMENT_WHILE,
        STATEMENT_FOR,
        STATEMENT_RETURN,
    };
    class Statement : public ParserResultPart {
        public:
            Statement(std::shared_ptr<ParserResultPart> statement,ParserStatementType_t type);
            std::shared_ptr<ParserResultPart> statement;
            const ParserStatementType_t type;
        protected:
        private:
    };
}
#endif // PARSER_STATEMENT_H
