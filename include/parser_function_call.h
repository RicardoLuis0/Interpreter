#ifndef PARSER_FUNCTION_CALL_H
#define PARSER_FUNCTION_CALL_H

#include <memory>
#include "parser_result_part.h"
#include "word_token.h"
#include "parser_expression_list.h"

namespace Parser{
    class FunctionCall:public ParserResultPart{
    public:
        FunctionCall(std::shared_ptr<Lexer::WordToken> identifier,std::shared_ptr<ExpressionList> arguments);
        std::shared_ptr<Lexer::WordToken> identifier;
        std::shared_ptr<ExpressionList> arguments;
    };
}

#endif // PARSER_FUNCTION_CALL_H
