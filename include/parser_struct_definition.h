#ifndef PARSER_STRUCT_DEFINITION_H
#define PARSER_STRUCT_DEFINITION_H

#include <vector>
#include <memory>
#include "parser_result_part.h"
#include "parser_member_definition.h"

namespace Parser{
    class StructDefinition:public ParserResultPart{
        public:
            StructDefinition(std::string name,std::vector<std::shared_ptr<MemberDefinition>> members,int line_start,int line_end);
            std::string name;
            std::vector<std::shared_ptr<MemberDefinition>> members;
    };
}

#endif // PARSER_STRUCT_DEFINITION_H
