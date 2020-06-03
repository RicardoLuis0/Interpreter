#ifndef PARSER_FUNCTION_DEFINITION_H
#define PARSER_FUNCTION_DEFINITION_H

#include "Lexer/WordToken.h"

#include "Parser/ParserResultPart.h"
#include "Parser/FunctionDefinitionParameter.h"
#include "Parser/CodeBlock.h"
#include <vector>

namespace Parser{
    class FunctionDefinition : public ParserResultPart {
    public:
        FunctionDefinition(parserProgress&);
        FunctionDefinition(int line_start,std::shared_ptr<VarType> return_type,std::shared_ptr<Lexer::WordToken> name,parserProgress&);//partial constructor
        FunctionDefinition(std::shared_ptr<VarType> return_type,std::shared_ptr<Lexer::WordToken> name,std::vector<std::shared_ptr<FunctionDefinitionParameter>> params,bool variadic,std::shared_ptr<VarType> variadic_type,std::shared_ptr<Lexer::WordToken> variadic_ident,std::shared_ptr<CodeBlock> code,int line_start,int line_end);
        std::shared_ptr<VarType> return_type;
        std::string name;
        std::vector<std::shared_ptr<FunctionDefinitionParameter>> parameters;
        bool variadic;
        std::shared_ptr<VarType> variadic_type;
        std::string variadic_ident;
        std::shared_ptr<CodeBlock> code;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    };
}

#endif // PARSER_FUNCTION_DEFINITION_H
