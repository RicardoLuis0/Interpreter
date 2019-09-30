#ifndef PARSER_FUNCTION_DEFINITION_H
#define PARSER_FUNCTION_DEFINITION_H

#include "lexer_word_token.h"

#include "parser_result_part.h"
#include "parser_function_definition_parameter.h"
#include "parser_code_block.h"
#include <vector>

namespace Parser{
    class FunctionDefinition : public ParserResultPart {
        public:
            FunctionDefinition(std::shared_ptr<VarType> return_type,std::shared_ptr<Lexer::WordToken>,std::vector<std::shared_ptr<FunctionDefinitionParameter>>,bool variadic,std::shared_ptr<VarType> variadic_type,std::shared_ptr<Lexer::Token> variadic_ident,std::shared_ptr<CodeBlock> code,int line_start,int line_end);
            std::shared_ptr<VarType> return_type;
            std::string name;
            std::vector<std::shared_ptr<FunctionDefinitionParameter>> parameters;
            bool variadic;
            std::shared_ptr<VarType> variadic_type;
            std::shared_ptr<Lexer::Token> variadic_ident;
            std::shared_ptr<CodeBlock> code;
    };
}

#endif // PARSER_FUNCTION_DEFINITION_H
