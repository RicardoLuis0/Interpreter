#ifndef PARSER_FUNCTION_CALL_H
#define PARSER_FUNCTION_CALL_H

#include <memory>
#include "parser_result_part.h"
#include "lexer_word_token.h"

#include "parser_expression_list.h"

namespace Parser{
    class FunctionCall:public ParserResultPart{
    public:
        FunctionCall(std::string identifier,std::shared_ptr<ExpressionList> arguments,int line_start,int line_end);
        std::string identifier;
        std::shared_ptr<ExpressionList> arguments;
    };
}

#endif // PARSER_FUNCTION_CALL_H
