#ifndef INTERPRETER_CODE_BLOCK_H
#define INTERPRETER_CODE_BLOCK_H

#include "parser_code_block.h"
#include "parser_line.h"
#include "interpreter_line.h"
#include "parser_statement.h"

namespace Interpreter {
    class CodeBlock : public Line {
        public:
            CodeBlock(class UserFunction * func,std::shared_ptr<Parser::CodeBlock>);//function constructor
            CodeBlock(DefaultFrame * parent,std::shared_ptr<Parser::CodeBlock>);//codeblock constructor
            CodeBlock(DefaultFrame * parent,std::shared_ptr<Parser::Line>);//single line block constructor (eg. IF statement with single line instead of block, etc)
            virtual std::shared_ptr<LineResult> run(std::shared_ptr<ExecFrame> context) override;
            void varDefCallback(std::shared_ptr<Parser::VariableDefinitionItem>);
        protected:
            CodeBlock(std::shared_ptr<DefaultFrame> frame,std::shared_ptr<Parser::CodeBlock> b);
            std::shared_ptr<DefaultFrame> default_frame;
            std::vector<std::shared_ptr<Line>> code;
            void addLine(std::shared_ptr<Parser::Line>);
            void addStatement(std::shared_ptr<Parser::Statement>);
    };
}

#endif // INTERPRETER_BLOCK_CODE_H
