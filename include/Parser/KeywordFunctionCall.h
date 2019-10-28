#ifndef PARSER_KEYWORD_FUNCTION_CALL_H
#define PARSER_KEYWORD_FUNCTION_CALL_H

#include <memory>
#include "Parser/ParserResultPart.h"
#include "Lexer/KeywordToken.h"
#include "Parser/VarType.h"
#include "Parser/ExpressionList.h"

namespace Parser {
    class KeywordFunctionCall : public ParserResultPart {
        public:
            KeywordFunctionCall(std::shared_ptr<Lexer::KeywordToken> id,std::shared_ptr<VarType> type,std::shared_ptr<ExpressionList> args,int line_start,int line_end);
            std::shared_ptr<Lexer::KeywordToken> identifier;
            std::shared_ptr<VarType> extra_type;
            std::shared_ptr<ExpressionList> arguments;
            virtual std::string getSource() override;
            virtual void print(int depth) override;
    };
}

#endif // PARSER_KEYWORD_FUNCTION_CALL_H
