#ifndef PARSER_CLASS_DEFINITION_H
#define PARSER_CLASS_DEFINITION_H

#include <memory>
#include "Parser/ParserResultPart.h"

namespace Parser{
    class ClassDefinition:public ParserResultPart{
        public:
            ClassDefinition(parserProgress&);
            ClassDefinition(int line_start,int line_end);
    };
}

#endif // PARSER_CLASS_DEFINITION_H
