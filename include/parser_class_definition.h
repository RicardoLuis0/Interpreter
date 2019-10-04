#ifndef PARSER_CLASS_DEFINITION_H
#define PARSER_CLASS_DEFINITION_H

#include <memory>
#include "parser_result_part.h"

namespace Parser{
    class ClassDefinition:public ParserResultPart{
        public:
            ClassDefinition(int line_start,int line_end);
    };
}

#endif // PARSER_CLASS_DEFINITION_H
