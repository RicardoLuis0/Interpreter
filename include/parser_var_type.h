#ifndef PARSER_VAR_TYPE_H
#define PARSER_VAR_TYPE_H

#include <memory>
#include "keyword_token.h"
#include "parser_result_part.h"

namespace Parser{
    enum ParserVarTypeType_t{
        VARTYPE_PRIMITIVE,
        //VARTYPE_IDENT,
    };
    class VarType : public ParserResultPart {
    public:
        VarType(std::shared_ptr<Lexer::KeywordToken> primitive);
        std::shared_ptr<Lexer::KeywordToken> primitive;
        const ParserVarTypeType_t type;
    };
}

#endif // PARSER_VAR_TYPE_H
