#ifndef PARSER_FUNCTION_DEFINITION_PARAMETER_H
#define PARSER_FUNCTION_DEFINITION_PARAMETER_H

#include "Lexer/WordToken.h"

#include "Parser/ResultPart.h"
#include "Parser/VarType.h"
#include <vector>

namespace Parser{
    class FunctionDefinitionParameter : public ParserResultPart {
        public:
            FunctionDefinitionParameter(std::shared_ptr<VarType>,std::shared_ptr<Lexer::WordToken>,bool is_reference,int line_start,int line_end);
            FunctionDefinitionParameter(std::shared_ptr<VarType>,std::string,bool is_reference,int line_start,int line_end);
            std::shared_ptr<VarType> type;
            std::string name;
            bool is_reference;
        protected:
        private:
    };
}

#endif // PARSER_FUNCTION_DEFINITION_PARAMETER_H
