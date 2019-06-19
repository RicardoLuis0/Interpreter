#ifndef PARSER_VARTYPE_MATCHER_H
#define PARSER_VARTYPE_MATCHER_H

#include "parser_component.h"
#include "parser_var_type.h"

namespace Parser{
    class VarTypeMatcher:public BaseComponent{
    public:
        std::shared_ptr<VarType> makeMatch(parserProgress&);
    };
}

#endif // PARSER_VARTYPE_MATCHER_H
