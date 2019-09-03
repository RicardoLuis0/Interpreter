#ifndef PARSER_VAR_TYPE_H
#define PARSER_VAR_TYPE_H

#include <vector>
#include <memory>
#include "lexer_keyword_token.h"

#include "parser_result_part.h"
#include "parser_expression.h"

namespace Parser{
    enum ParserVarTypeType_t{
        VARTYPE_VOID,
        VARTYPE_PRIMITIVE,
        VARTYPE_IDENTIFIER,
    };
    enum ParserPrimitiveType_t{
        PRIMITIVE_INVALID,
        PRIMITIVE_ANY,
        PRIMITIVE_TYPE,
        PRIMITIVE_INT,
        PRIMITIVE_CHAR,
        PRIMITIVE_FLOAT,
        PRIMITIVE_STRING,
    };
    class VarType : public ParserResultPart {
    public:
        VarType(std::shared_ptr<Lexer::KeywordToken> primitive,bool is_const,bool has_sign,bool sign,int line_start,int line_end);
        VarType(ParserPrimitiveType_t primitive,bool is_const,bool has_sign,bool sign,int line_start,int line_end);
        ParserPrimitiveType_t primitive;
        ParserVarTypeType_t type;
        bool has_sign;
        bool sign;
        bool is_const;
        std::vector<std::shared_ptr<Expression>> array_sizes;
    };
}

#endif // PARSER_VAR_TYPE_H
