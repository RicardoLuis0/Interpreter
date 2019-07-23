#ifndef PARSER_VAR_TYPE_H
#define PARSER_VAR_TYPE_H

#include <memory>
#include "keyword_token.h"
#include "parser_result_part.h"

namespace Parser{
    enum ParserVarTypeType_t{
        VARTYPE_VOID,
        VARTYPE_PRIMITIVE,
        VARTYPE_IDENTIFIER,
    };
    enum ParserPrimitiveType_t{
        PRIMITIVE_INVALID,
        PRIMITIVE_INT,
        PRIMITIVE_FLOAT,
        PRIMITIVE_STRING,
    };
    class VarType : public ParserResultPart {
    public:
        VarType(std::shared_ptr<Lexer::KeywordToken> primitive);
        VarType(ParserPrimitiveType_t primitive);
        ParserPrimitiveType_t primitive;
        ParserVarTypeType_t type;
    private:
    };
}

#endif // PARSER_VAR_TYPE_H
