#ifndef PARSER_VAR_TYPE_H
#define PARSER_VAR_TYPE_H

#include <vector>
#include <memory>
#include "Lexer/KeywordToken.h"
#include "Parser/ParserResultPart.h"
#include "Parser/Expression.h"

namespace Parser{
    enum ParserVarTypeType_t{
        VARTYPE_VOID,
        VARTYPE_PRIMITIVE,
        VARTYPE_IDENTIFIER,
        VARTYPE_DECLTYPE,
    };
    enum ParserPrimitiveType_t{
        PRIMITIVE_INVALID,
        PRIMITIVE_POINTER,
        PRIMITIVE_ANY,
        PRIMITIVE_TYPE,
        PRIMITIVE_INT,
        PRIMITIVE_CHAR,
        PRIMITIVE_FLOAT,
        PRIMITIVE_STRING,
    };
    class VarType : public ParserResultPart {
    public:
        VarType(parserProgress&);
        VarType(std::shared_ptr<Lexer::KeywordToken> primitive,bool is_const,bool has_sign,bool sign,std::shared_ptr<VarType> extra,int line_start,int line_end);
        VarType(std::shared_ptr<Expression> decltype_expr,bool is_const,int line_start,int line_end);
        VarType(ParserPrimitiveType_t primitive,bool is_const,bool has_sign,bool sign,std::shared_ptr<VarType> extra,int line_start,int line_end);
        ParserVarTypeType_t type;
        ParserPrimitiveType_t primitive;
        bool has_sign;
        bool sign;
        bool is_const;
        std::vector<std::shared_ptr<Expression>> array_sizes;
        std::shared_ptr<VarType> extra;
        std::shared_ptr<Expression> decltype_expr;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_VAR_TYPE_H
