#ifndef PARSER_DEFINITION_H
#define PARSER_DEFINITION_H

#include <memory>
#include "Parser/ParserResultPart.h"

namespace Parser{
    enum ParserDefinitionType_t{
        DEFINITION_VAR,
        DEFINITION_FUNC,
        DEFINITION_STRUCT,
    };
    class Definition : public ParserResultPart {
        public:
            Definition(parserProgress&);
            Definition(ParserDefinitionType_t type,std::shared_ptr<ParserResultPart> def,int line_start,int line_end);
            ParserDefinitionType_t type;
            std::shared_ptr<ParserResultPart> def;
            virtual std::string getSource(int indent) override;
            virtual void print(int depth) override;
    };
}

#endif // PARSER_DEFINITION_H
