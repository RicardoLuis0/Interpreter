#ifndef PARSER_CLASS_DEFINITION_H
#define PARSER_CLASS_DEFINITION_H

#include <memory>
#include "Parser/ResultPart.h"

namespace Parser{
    class ClassDefinition:public ParserResultPart{
        public:
            ClassDefinition(int line_start,int line_end);
    };
}

#endif // PARSER_CLASS_DEFINITION_H
