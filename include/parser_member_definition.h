#ifndef PARSER_MEMBER_DEFINITION_H
#define PARSER_MEMBER_DEFINITION_H

#include <memory>
#include "parser_result_part.h"

namespace Parser{
    enum member_scope_t{
        MEMBER_NONE,
        //MEMBER_MODULE,
        MEMBER_PUBLIC,
        MEMBER_PROTECTED,
        MEMBER_PRIVATE,
    };
    enum member_type_t{
        MEMBER_DEFAULT,
        MEMBER_STATIC,
        MEMBER_VIRTUAL,
    };
    class MemberDefinition:public ParserResultPart{
        public:
            MemberDefinition(int line_start,int line_end);
            bool is_override;
            member_scope_t scope;
            member_type_t type;
            std::shared_ptr<ParserResultPart> member;
    };
}

#endif // PARSER_MEMBER_DEFINITION_H
