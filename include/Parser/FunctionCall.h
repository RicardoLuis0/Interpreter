#ifndef PARSER_FUNCTION_CALL_H
#define PARSER_FUNCTION_CALL_H

#include <memory>
#include "Parser/ResultPart.h"
#include "Lexer/WordToken.h"

#include "Parser/ExpressionList.h"

namespace Parser{
    class FunctionCall:public ParserResultPart{
    public:
        FunctionCall(std::string identifier,std::shared_ptr<ExpressionList> arguments,int line_start,int line_end);
        std::string identifier;
        std::shared_ptr<ExpressionList> arguments;
    };
}

#endif // PARSER_FUNCTION_CALL_H
