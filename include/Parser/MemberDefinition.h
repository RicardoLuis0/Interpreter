#ifndef PARSER_MEMBER_DEFINITION_H
#define PARSER_MEMBER_DEFINITION_H

#include <memory>
#include "Parser/ParserResultPart.h"

namespace Parser{
    enum member_scope_t{
        MEMBER_SCOPE_DEFAULT,
        //MEMBER_SCOPE_MODULE,
        MEMBER_SCOPE_PUBLIC,
        MEMBER_SCOPE_PROTECTED,
        MEMBER_SCOPE_PRIVATE,
    };
    enum member_modifier_t{
        MEMBER_MOD_NONE,
        MEMBER_MOD_STATIC,
        MEMBER_MOD_VIRTUAL,
    };
    enum member_type_t{
        MEMBER_TYPE_VARIABLE,
        MEMBER_TYPE_FUNCTION,
    };
    class MemberDefinition:public ParserResultPart{
    public:
        MemberDefinition(parserProgress&);
        MemberDefinition(bool is_override,member_scope_t scope,member_modifier_t mod,member_type_t type,std::shared_ptr<ParserResultPart> member,int line_start,int line_end);
        bool is_override;
        member_scope_t scope;
        member_modifier_t mod;
        member_type_t type;
        std::shared_ptr<ParserResultPart> member;
        virtual std::string getSource() override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_MEMBER_DEFINITION_H
