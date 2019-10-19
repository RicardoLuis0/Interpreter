#ifndef PARSER_DEFINITION_H
#define PARSER_DEFINITION_H

#include <memory>
#include "Parser/ResultPart.h"

namespace Parser{
    enum ParserDefinitionType_t{
        DEFINITION_VAR,
        DEFINITION_FUNC,
        DEFINITION_STRUCT,
    };
    class Definition : public ParserResultPart {
        public:
            Definition(ParserDefinitionType_t type,std::shared_ptr<ParserResultPart> def,int line_start,int line_end);
            ParserDefinitionType_t type;
            std::shared_ptr<ParserResultPart> def;
    };
}

#endif // PARSER_DEFINITION_H
