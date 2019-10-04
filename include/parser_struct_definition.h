#ifndef PARSER_STRUCT_DEFINITION_H
#define PARSER_STRUCT_DEFINITION_H

#include <memory>
#include "parser_result_part.h"

namespace Parser{
    class StructDefinition:public ParserResultPart{
        public:
            StructDefinition(int line_start,int line_end);
            std::vector<std::shared_ptr<MemberDefinition>> vars;
            std::vector<std::shared_ptr<MethodDefinition>> funcs;
    };
}

#endif // PARSER_STRUCT_DEFINITION_H
