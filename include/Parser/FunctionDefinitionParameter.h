#ifndef PARSER_FUNCTION_DEFINITION_PARAMETER_H
#define PARSER_FUNCTION_DEFINITION_PARAMETER_H

#include "Lexer/WordToken.h"

#include "Parser/ParserResultPart.h"
#include "Parser/VarType.h"
#include <vector>

namespace Parser{
    class FunctionDefinitionParameter : public ParserResultPart {
    public:
        FunctionDefinitionParameter(parserProgress&);
        FunctionDefinitionParameter(int line_start,std::shared_ptr<VarType>,parserProgress&);//partial constructor
        FunctionDefinitionParameter(std::shared_ptr<VarType>,std::shared_ptr<Lexer::WordToken>,bool is_reference,int line_start,int line_end);
        FunctionDefinitionParameter(std::shared_ptr<VarType>,std::string,bool is_reference,int line_start,int line_end);
        std::shared_ptr<VarType> type;
        std::string name;
        bool is_reference;
        virtual std::string getSource(int indent) override;
        virtual void print(int depth) override;
    protected:
    private:
    };
}

#endif // PARSER_FUNCTION_DEFINITION_PARAMETER_H
