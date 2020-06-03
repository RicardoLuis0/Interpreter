#ifndef PARSER_FUNCTION_CALL_H
#define PARSER_FUNCTION_CALL_H

#include <memory>
#include "Parser/ParserResultPart.h"
#include "Lexer/WordToken.h"

#include "Parser/ExpressionList.h"

namespace Parser{
    class FunctionCall:public ParserResultPart{
    public:
        FunctionCall(parserProgress&);
        FunctionCall(std::string identifier,std::shared_ptr<ExpressionList> arguments,int line_start,int line_end);
        std::string identifier;
        std::shared_ptr<ExpressionList> arguments;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_FUNCTION_CALL_H
