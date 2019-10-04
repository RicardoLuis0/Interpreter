#ifndef PARSER_MEMBER_DEFINITION_H
#define PARSER_MEMBER_DEFINITION_H

#include <memory>
#include "parser_result_part.h"

namespace Parser{
    class MemberDefinition:public ParserResultPart{
        public:
            MemberDefinition(int line_start,int line_end);
    };
}

#endif // PARSER_MEMBER_DEFINITION_H
