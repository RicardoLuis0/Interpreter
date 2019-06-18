#ifndef PARSER_STATEMENT_H
#define PARSER_STATEMENT_H

#include "parser_result_part.h"
#include <memory>

namespace Parser{
    enum ParserStatementType_t{
        STATEMENT_IF,
        STATEMENT_WHILE,
        STATEMENT_FOR,
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
