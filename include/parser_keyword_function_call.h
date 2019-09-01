#ifndef PARSER_KEYWORD_FUNCTION_CALL_H
#define PARSER_KEYWORD_FUNCTION_CALL_H

#include <memory>
#include "parser_result_part.h"
#include "lexer_keyword_token.h"
#include "parser_var_type.h"
#include "parser_expression_list.h"

namespace Parser {
    class KeywordFunctionCall : public ParserResultPart {
        public:
            KeywordFunctionCall(std::shared_ptr<Lexer::KeywordToken> id,std::shared_ptr<VarType> type,std::shared_ptr<ExpressionList> args,int line_start,int line_end);
            std::shared_ptr<Lexer::KeywordToken> identifier;
            std::shared_ptr<VarType> extra_type;
            std::shared_ptr<ExpressionList> arguments;
    };
}

#endif // PARSER_KEYWORD_FUNCTION_CALL_H
